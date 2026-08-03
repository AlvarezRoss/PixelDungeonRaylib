#include "helper.h"


int InitAnimation(Animation* animation, const char* path, int frameNumber)
{
    if (animation == NULL) return 1;
    
    Image image = LoadImage(path);
    if (image.data == NULL) return 1;
    animation->texture = LoadTextureFromImage(image);
    if (animation->texture.id == 0) return 1;
    animation->currentFrame = 0;
    animation->frameCounter = 0;
    // (Rectangle) is a compound literal aka a temporary struct i can create to them assign it to the frameRect
    animation->frameRect = (Rectangle){0.0f,0.0f,(float)animation->texture.width/frameNumber,(float)animation->texture.height};
    animation->frameSpeed = 6;
    animation->frameNum = frameNumber;
    animation->frameWidth = (float)animation->texture.width/animation->frameNum;
    animation->rotated = false;
    UnloadImage(image);
    return 0;
}


int InitCharacter(Character* character, Graphics* graphics)
{
    if(character == NULL || graphics == NULL) return -1;

    character->graphics = graphics;
    character->animation = character->graphics->idleAnimation;
    character->entityState = STATE_IDLE;
    character->health = 40;
    character->speed = (Vector2){0,0};
    character->rotated = false;
    character->collisionRect = (Rectangle){character->animation->frameRect.width/2,character->animation->frameRect.height/2,SPRITELEN,SPRITEHEIGHT};
    return 0;
}

void UpdateCharacterAnimation(Character* character)
{
    character->animation->frameCounter++;
    // the if statement body is to control how many game frames to wait before switching animation 60/8 = 7.5 -> those are the game frames to wait
    if (character->animation->frameCounter >= (60/character->animation->frameSpeed))
    {
        character->animation->frameCounter = 0; // Reset the frame counter to restart the wait time
        character->animation->currentFrame ++;

        if (character->animation->currentFrame >= character->animation->frameNum)
        {
            character->animation->currentFrame = 0; // animation restart
            if (character->entityState == STATE_ATTACKING)
            {
                character->entityState = STATE_IDLE;
                if (character->entityType != ENTITY_PLAYER) StartTimer(character->attackTimer,5.0f);
            } 
            if (character->entityState == STATE_HURT) character->entityState = STATE_IDLE;
            if (character->entityState == STATE_DEAD && character->entityType != ENTITY_PLAYER) character->Postion.x += 1000000;
        } 

        character->animation->frameRect.x = (float)character->animation->currentFrame * character->animation->frameWidth;
    }   
}

Rectangle HandleCharacterRotation(Character* character)
{
    // To "Turn a sprite around" we shift the width from positive to negative
    Rectangle animCopy = character->animation->frameRect;
    if (character->rotated) animCopy.width = - character->animation->frameRect.width;
    return animCopy;
}

// In these two functions I have set the camera to be the characters position + 50 or 40. They are of yet arbitrary numbers that look good for now
int InitCamera(Camera2D* camera, Character* player, Rectangle window)
{
    if (camera == NULL) return 1;
    if (player == NULL) return 1;

    camera->target = (Vector2){player->Postion.x + 50, player->Postion.y + 40};
    camera->zoom = 4.0f;
    camera->offset = (Vector2){window.width/2.0f,window.height/2.0f};
    camera->rotation = 0.0f;
    return 0;
}

void UpdateCharacterCamera(Camera2D* camera, Character* character) // Funtion is needed to change the camera focus from the player to their companions - TO BE IMPLEMENTED
{
    if (camera== NULL || character ==  NULL) return;

    camera->target = (Vector2){character->Postion.x + 50, character->Postion.y + 40};
    return;
}

void StartTimer(Timer* timer, float lifetime)
{
    if (timer == NULL) return;

    timer->lifetime = lifetime;
    return;
}

void UpdateTimer(Timer* timer)
{
    if(timer == NULL) return;

    timer->lifetime -= GetFrameTime();
}

int TimerFinished(Timer* timer)
{
    if (timer == NULL) return -1; 
    if (timer->lifetime > 0.0f) return 1;
    return 0;
}
void FullScreen(float* windowWidth, float* windowHeight, Camera2D* camera)
{
    if(camera == NULL) return;
    if(!IsWindowFullscreen())
    {
        int monitor = GetCurrentMonitor();
        *windowWidth = (float)GetMonitorWidth(monitor);
        *windowHeight = (float)GetMonitorHeight(monitor);
        SetWindowSize(*windowWidth,*windowHeight);
        ToggleFullscreen();
    }
    else
    {
        ToggleFullscreen();
        *windowHeight = (float)WINDOWED_MODE_SIZE;
        *windowWidth = (float)WINDOWED_MODE_SIZE;
        SetWindowSize(*windowWidth,*windowHeight);
    }

    camera->offset = (Vector2){*windowWidth/2.0f,*windowHeight/2.0f};
}

int InitGameState(GameState* gameState)
{
    if (gameState == NULL) return -1;

    gameState->State = GAME_STATE_RUNNING;
    gameState->level = 1;
    gameState->targetFps = 60;
    return 0;
}

int GameStateInputHandle(GameState* gameState)
{
    if (gameState == NULL) return -1;
    if (IsKeyPressed(KEY_SPACE))
    {
        if (gameState->State == GAME_STATE_RUNNING) gameState->State = GAME_STATE_PAUSED;
        else gameState->State = GAME_STATE_RUNNING;
        return 0;
    }

    if (IsKeyPressed(KEY_F2))
    {
        if (gameState->State != GAME_STATE_IN_EDITOR) gameState->State = GAME_STATE_IN_EDITOR;
        else gameState->State = GAME_STATE_RUNNING;
        return 0;
    }

    if (IsKeyPressed(KEY_ENTER) && gameState->State == GAME_STATE_IN_EDITOR) gameState->State = GAME_STATE_UNINITIALIZED_CUSTON_MAP;

    return 0;
}

int InitGraphics(Graphics* graphics, ENTITY_TYPE entity)
{
    if (graphics == NULL) return -1;
    graphics->idleAnimation = malloc(sizeof(Animation));
    if (graphics->idleAnimation == NULL) return -1;
    graphics->walkingAnimation = malloc(sizeof(Animation));
    if (graphics->walkingAnimation == NULL) return -1;
    graphics->attackAnimation = malloc(sizeof(Animation));
    if (graphics->attackAnimation == NULL) return -1;
    graphics->deathAnimation = malloc(sizeof(Animation));
    if (graphics->deathAnimation == NULL) return -1;
    graphics->hurtAnimation = malloc(sizeof(Animation));
    if (graphics->hurtAnimation == NULL) return -1;

    switch (entity)
    {
    case ENTITY_PLAYER:
        if (InitAnimation(graphics->idleAnimation,"Assets/Characters/Characters(100x100)/Knight/Knight/Knight-Idle.png",6) != 0) return -1;
        if (InitAnimation(graphics->walkingAnimation,"Assets/Characters/Characters(100x100)/Knight/Knight/Knight-Walk.png",8) != 0) return -1;
        if (InitAnimation(graphics->attackAnimation,"Assets/Characters/Characters(100x100)/Knight/Knight/Knight-Attack01.png", 7) != 0) return -1;
        if (InitAnimation(graphics->hurtAnimation,"Assets/Characters/Characters(100x100)/Knight/Knight/Knight-Hurt.png",4) != 0) return -1;
        if (InitAnimation(graphics->deathAnimation,"Assets/Characters/Characters(100x100)/Knight/Knight/Knight-Death.png",4) != 0) return -1;
        break;
    case ENTITY_ORC:
        if (InitAnimation(graphics->idleAnimation,"Assets/Characters/Characters(100x100)/Orc/Orc/Orc-Idle.png",6) != 0) return -1;
        if (InitAnimation(graphics->walkingAnimation,"Assets/Characters/Characters(100x100)/Orc/Orc/Orc-Walk.png",8) != 0) return -1;
        if (InitAnimation(graphics->attackAnimation,"Assets/Characters/Characters(100x100)/Orc/Orc/Orc-Attack01.png",6) != 0) return -1;
        if (InitAnimation(graphics->hurtAnimation,"Assets/Characters/Characters(100x100)/Orc/Orc/Orc-Hurt.png",4) != 0) return -1;
        if (InitAnimation(graphics->deathAnimation,"Assets/Characters/Characters(100x100)/Orc/Orc/Orc-Death.png",4) != 0) return -1;
        break;
    
    case ENTITY_SKELLETON:
        if (InitAnimation(graphics->idleAnimation,"Assets/Characters/Characters(100x100)/Skeleton/Skeleton/Skeleton-Idle.png",6)) return -1;
        if (InitAnimation(graphics->walkingAnimation,"Assets/Characters/Characters(100x100)/Skeleton/Skeleton/Skeleton-Walk.png",8)) return -1;
        if (InitAnimation(graphics->attackAnimation,"Assets/Characters/Characters(100x100)/Skeleton/Skeleton/Skeleton-Attack01.png",6)) return -1;
        if (InitAnimation(graphics->hurtAnimation,"Assets/Characters/Characters(100x100)/Skeleton/Skeleton/Skeleton-Hurt.png",4)) return -1;
        if (InitAnimation(graphics->deathAnimation,"Assets/Characters/Characters(100x100)/Skeleton/Skeleton/Skeleton-Death.png",4)) return -1;
        break;
    default:
        return -1;
    }
    
    return 0;
}

void DeinitGraphics(Graphics* graphics)
{
    UnloadTexture(graphics->idleAnimation->texture);
    UnloadTexture(graphics->walkingAnimation->texture);
    UnloadTexture(graphics->attackAnimation->texture);
    UnloadTexture(graphics->hurtAnimation->texture);
    UnloadTexture(graphics->deathAnimation->texture);

    free(graphics->idleAnimation);
    free(graphics->walkingAnimation);
    free(graphics->attackAnimation);
    free(graphics->hurtAnimation);
    free(graphics->deathAnimation);
}
int InitPlayer(Character* player, Graphics* graphics, float x, float y)
{
    if (player == NULL || graphics == NULL) return -1;
    if (InitCharacter(player,graphics) != 0) return -1;
    player->entityType = ENTITY_PLAYER;
    player->maxHealth = 40;
    player->health = player->maxHealth;
    player->attackTimer = NULL;
    player->Postion.x = x;
    player->Postion.y = y;
    return 0;
}

int InitEnemy(Character* enemy, ENTITY_TYPE entity, Graphics* graphics,float x, float y)
{ // If this funtion returns 1 the program will quit so I don't call free on allocated memory
    if (enemy == NULL) return -1;
    enemy->attackTimer = malloc(sizeof(Timer));
    if (enemy->attackTimer == NULL) return 1;
    if (enemy == NULL || graphics == NULL) return -1;
    if (InitCharacter(enemy,graphics) != 0) return -1;

    enemy->entityType = entity;
    enemy->entityState = STATE_IDLE;
    enemy->detectionArea.center = (Vector2){enemy->collisionRect.x,enemy->collisionRect.y};
    enemy->detectionArea.radius = 50.0f;
    enemy->detectionArea.color = BLUE;
    enemy->attackTimer->lifetime = 0.0f;
    enemy->Postion.x = x;
    enemy->Postion.y = y;
    return 0;

}


void DeinitPlayer(Character* player)
{
    if (player == NULL) return;
    player->animation = NULL;
    if (player->attackTimer != NULL) free(player->attackTimer);
}

