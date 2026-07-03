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
    animation->frameSpeed = 10;
    animation->frameNum = frameNumber;
    animation->frameWidth = (float)animation->texture.width/animation->frameNum;
    animation->rotated = false;
    UnloadImage(image);
    return 0;
}


int InitCharacter(Character* character, Animation* idleAnimation, Animation* walkAnimation, Animation* attackAnimation, Animation* hurtAnimation)
{
    if(character == NULL || idleAnimation == NULL || walkAnimation == NULL || attackAnimation == NULL || hurtAnimation == NULL) return 1;

    character->idleAnimation = idleAnimation;
    character->walkingAnimation = walkAnimation;
    character->attackAnimation = attackAnimation;
    character->hurtAnimation = hurtAnimation;
    character->animation = character->idleAnimation;
    character->entityState = STATE_IDLE;
    character->health = 40;
    character->speed = (Vector2){0,0};
    character->Postion = (Vector2){800/2,450/2};
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
            if (character->animation == character->attackAnimation) character->entityState = STATE_IDLE;
            if (character->animation == character->hurtAnimation) character->entityState = STATE_IDLE;
        } 

        character->animation->frameRect.x = (float)character->animation->currentFrame * character->animation->frameWidth;
    }

    character->collisionRect.x = character->Postion.x + (character->animation->frameWidth/2.0f) - 10;
    character->collisionRect.y = character->Postion.y + (character->animation->texture.height/2.0f) - 10;
        
}

void HandleCharacterRotation(Character* character)
{
    // To "Turn a sprite around" we shift the width from positive to negative
    if (character->rotated && !character->animation->rotated)
    {
        character->animation->frameRect.width = -character->animation->frameRect.width;

        character->animation->rotated = true;
    }
    else if (!character->rotated && character->animation->rotated)
    {
        character->animation->frameRect.width = - character->animation ->frameRect.width;
        character->animation->rotated = false;
    }
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
