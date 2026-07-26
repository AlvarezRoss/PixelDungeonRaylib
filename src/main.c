
#include "helper.h"
#include "map.h"
#include "enemyBehaviours.h"
#include "editor.h"

int InitPlayer(Character* player);
void DeinitPlayer(Character* player);
void PlayerMovement(Character* player);
void EnemyMovement(Character* enemy, Character* player);
int InitEnemy(Character* enemy, char* enemyType);
void EnemyAttack(Character* enemy, Character* player);
void UpdateCharacterPosition(Character* character);
void HandlePlayerAttack(Character* player, Character* enemies);
void TakeDamage(Character* character, int damage);
void ProcGameLoop(Character* player, Character* enemies, LevelData* levelData, TileSet* tileSet, Camera2D* camera);
void DrawGameLoop(Camera2D* camera, LevelData* levelData, TileSet* tileSet, Character* player, Character* enemies);

int main(void)
{
    Rectangle window = {0,0,WINDOWED_MODE_SIZE,WINDOWED_MODE_SIZE};    
    InitWindow(window.height,window.width,"My first Window");

    TileSet* tileSet = malloc(sizeof(TileSet));
    Character player;
    Character enemies[ENEMIES_IN_LEVEL_ONE];
    LevelData levelData;
    levelData.initPosition = (Vector2){300,300};
    if (InitPlayer(&player) != 0) return 1;
    if (InitiTileSet(tileSet) != 0) return 1;
    

    player.Postion.y = levelData.initPosition.y - 20;
    player.Postion.x = levelData.initPosition.x + 20;

    if (InitEnemy(&enemies[0],"orc") != 0) return 1;

    enemies[0].Postion.y = levelData.initPosition.y - 10;
    enemies[0].Postion.x = levelData.initPosition.x + 30;

    Camera2D camera = {0};
    if (InitCamera(&camera,&player,window) != 0) return 1;

    GameState gameState;
    if(InitGameState(&gameState) != 0) return 1;
    SetTargetFPS(gameState.targetFps);
    

    while(!WindowShouldClose())
    {
        if(IsKeyPressed(KEY_F1)) FullScreen(&window.width,&window.height,&camera);
        GameStateInputHandle(&gameState);
        if (gameState.State == GAME_STATE_RUNNING)
        {
            ProcGameLoop(&player,enemies,&levelData,tileSet,&camera);
        }
        
        //-----------------------------------------------------------
        //                Draw
        //-----------------------------------------------------------
        
        BeginDrawing();
            if (gameState.State == GAME_STATE_RUNNING)
            {
                DrawGameLoop(&camera,&levelData,tileSet,&player,enemies);
            }
            else if (gameState.State == GAME_STATE_IN_EDITOR)
            {
                InitEditor(window, tileSet);
            }
            
        EndDrawing();
    }

    // ----------------------------------------------------------------
    // DEINIT
    // ----------------------------------------------------------------
    
    DeinitPlayer(&player);
    DeinitPlayer(&enemies[0]); // Unsure if I need to have another function for enemy characters or just rename the function
    DeInitTileSet(tileSet);
    tileSet = NULL;
    CloseWindow();
    
    return 0;    
}

void ProcGameLoop(Character* player, Character* enemies, LevelData* levelData, TileSet* tileSet, Camera2D* camera)
{
    PlayerMovement(player);
    HandleGroundCollision(levelData,tileSet,player);
    HandlePlayerAttack(player,enemies);
    UpdateCharacterAnimation(player);
    UpdateCharacterPosition(player);
    HandleCharacterRotation(player);
        

    UpdateCharacterCamera(camera,player);
        
    EnemyMovement(&enemies[0], player);
    EnemyAttack(&enemies[0],player);
    HandleGroundCollision(levelData,tileSet,&enemies[0]);
    UpdateCharacterAnimation(&enemies[0]);
    HandleCharacterRotation(&enemies[0]);
    UpdateCharacterPosition(&enemies[0]);
}
void DrawGameLoop(Camera2D* camera, LevelData* levelData, TileSet* tileSet, Character* player, Character* enemies)
{
    ClearBackground((Color){37,19,26,255});
            
    BeginMode2D(*camera);
        DrawGroundLayer(levelData,tileSet);
        DrawObjectLayer(levelData,tileSet,player); // for now I need to pass the a player pointer... PENDING REFACTOR
        DrawTextureRec(enemies[0].animation->texture,enemies[0].animation->frameRect,enemies[0].Postion,WHITE);
        DrawTextureRec(player->animation->texture,player->animation->frameRect,player->Postion,WHITE);
    EndMode2D();
}
/*
    We use different init functions for the player and the enemies to handle the specefic paths to the different animation sprites
*/
int InitPlayer(Character* player)
{
    Animation* idleAnimation = malloc(sizeof(Animation));
    Animation* walkingAnimation = malloc(sizeof(Animation));
    Animation* attackAnimation = malloc(sizeof(Animation));
    Animation* hurtAnimation = malloc(sizeof(Animation));
    Animation* deathAnimation = malloc(sizeof(Animation));

    if (InitAnimation(idleAnimation,"Assets/Characters/Characters(100x100)/Knight/Knight/Knight-Idle.png",6) != 0) return 1;
    if (InitAnimation(walkingAnimation,"Assets/Characters/Characters(100x100)/Knight/Knight/Knight-Walk.png",8) != 0) return 1;
    if (InitAnimation(attackAnimation,"Assets/Characters/Characters(100x100)/Knight/Knight/Knight-Attack01.png", 7) != 0) return 1;
    if (InitAnimation(hurtAnimation,"Assets/Characters/Characters(100x100)/Knight/Knight/Knight-Hurt.png",4) != 0) return 1;
    if (InitAnimation(deathAnimation,"Assets/Characters/Characters(100x100)/Knight/Knight/Knight-Death.png",4) != 0) return 1;
    if (InitCharacter(player,idleAnimation, walkingAnimation, attackAnimation, hurtAnimation, deathAnimation) != 0) return 1;
    player->entityType = ENTITY_PLAYER;
    player->maxHealth = 40;
    player->health = player->maxHealth;
    player->attackTimer = NULL;
    return 0;
}

int InitEnemy(Character* enemy, char* enemyType)
{ // If this funtion returns 1 the program will quit so I don't call free on allocated memory
    if (enemy == NULL || enemyType == NULL) return 1;
    //if (strcmp(enemyType,"") != 0) return 1;

    Animation* idleAnimation = malloc(sizeof(Animation));
    Animation* walkAnimation = malloc(sizeof(Animation));
    Animation* attackAnimation = malloc(sizeof(Animation));
    Animation* hurtAnimation = malloc(sizeof(Animation));
    Animation* deathAnimation = malloc(sizeof(Animation));
    enemy->attackTimer = malloc(sizeof(Timer));
    if (enemy->attackTimer == NULL) return 1;

    // TODO -- ENEMY TYPES!!!

    if (InitAnimation(idleAnimation,"Assets/Characters/Characters(100x100)/Orc/Orc/Orc-Idle.png",6) != 0) return 1;
    if (InitAnimation(walkAnimation,"Assets/Characters/Characters(100x100)/Orc/Orc/Orc-Walk.png",8) != 0) return 1;
    if (InitAnimation(attackAnimation,"Assets/Characters/Characters(100x100)/Orc/Orc/Orc-Attack01.png",6) != 0) return 1;
    if (InitAnimation(hurtAnimation,"Assets/Characters/Characters(100x100)/Orc/Orc/Orc-Hurt.png",4) != 0) return 1;
    if (InitAnimation(deathAnimation,"Assets/Characters/Characters(100x100)/Orc/Orc/Orc-Death.png",4) != 0) return 1; 
    if (InitCharacter(enemy,idleAnimation,walkAnimation,attackAnimation,hurtAnimation,deathAnimation) != 0) return 1;

    enemy->entityType = ENTITY_ORC;
    enemy->entityState = STATE_IDLE;
    enemy->detectionArea.center = (Vector2){enemy->collisionRect.x,enemy->collisionRect.y};
    enemy->detectionArea.radius = 50.0f;
    enemy->detectionArea.color = BLUE;
    enemy->attackTimer->lifetime = 0.0f;
    return 0;

}


void DeinitPlayer(Character* player)
{
    if (player == NULL) return;

    player->animation = NULL;

    UnloadTexture(player->idleAnimation->texture);
    UnloadTexture(player->attackAnimation->texture);
    UnloadTexture(player->walkingAnimation->texture);
    UnloadTexture(player->hurtAnimation->texture);
    
    free(player->idleAnimation);
    free(player->attackAnimation);
    free(player->walkingAnimation);
    free(player->hurtAnimation);
    if (player->attackTimer != NULL) free(player->attackTimer);
}

void PlayerMovement(Character* player)
{
    if (player == NULL) return;
    if (player->entityState == STATE_DEAD) return;
    if (player->entityState == STATE_HURT) return;
    // IDLE
    if (GetKeyPressed() == 0 && player->entityState != STATE_ATTACKING)
    {
        player->entityState = STATE_IDLE;
        if (player->animation != player->idleAnimation) player->animation = player->idleAnimation;
    }
    // MOVEMENT
    if (IsKeyDown(KEY_A) && player->entityState != STATE_ATTACKING)
    {
        if (player->animation != player->walkingAnimation) player->animation = player->walkingAnimation;
        player->entityState = STATE_WALKING;
        player->speed.x = -1;
        if (!player->rotated) player->rotated = true;
    }
    else if (IsKeyDown(KEY_D) && player->entityState != STATE_ATTACKING)
    {
        if (player->animation != player->walkingAnimation) player->animation = player->walkingAnimation;
        player->entityState = STATE_WALKING;
        player->speed.x = 1;
        if (player->rotated) player->rotated = false;
    }
    else
    {
        player->speed.x = 0;
    }


    if (IsKeyDown(KEY_W) && player->entityState != STATE_ATTACKING)
    {
        if (player->animation != player->walkingAnimation) player->animation = player->walkingAnimation;
        player->entityState = STATE_WALKING;
        player->speed.y = -1;
    }
    else if (IsKeyDown(KEY_S) && player->entityState != STATE_ATTACKING)
    {
        if (player->animation != player->walkingAnimation) player->animation = player->walkingAnimation;
        player->entityState = STATE_WALKING;
        player->speed.y = 1;
    }
    else
    {
        player->speed.y = 0;
    }
}

// TODO - actually move -- Should handle movement and state control in different functions
void EnemyMovement(Character* enemy, Character* player)
{
    if (enemy == NULL || player == NULL) return;
    if (enemy->entityState == STATE_HURT) return;
    if (enemy->entityState == STATE_DEAD) return;
    enemy->detectionArea.center = (Vector2){enemy->collisionRect.x,enemy->collisionRect.y};

    if (CheckCollisionCircleRec(enemy->detectionArea.center,enemy->detectionArea.radius,player->collisionRect) && 
            (enemy->entityState != STATE_HURT && enemy->entityState != STATE_ATTACKING)) 
    {
        enemy->entityState = STATE_FOLLOWING;
        ChasePlayer(enemy,player);
        return;
    }
        
    if (enemy->entityState == STATE_IDLE)
    {
        if (enemy->animation != enemy->idleAnimation) enemy->animation = enemy->idleAnimation;
        enemy->speed = (Vector2){0.0f,0.0f};
        return;
    }

    enemy->entityState = STATE_IDLE;
    
}

void EnemyAttack(Character* enemy, Character* player) // TODO- IMPLEMENTING HIT LOGIC
{
    if (enemy == NULL || player == NULL) return;
    if(enemy->entityState == STATE_HURT || enemy->entityState == STATE_DEAD) return;
    bool playerCollision = CheckCollisionRecs(enemy->collisionRect, player->collisionRect);
    if (TimerFinished(enemy->attackTimer) == 1) UpdateTimer(enemy->attackTimer);
    if (!playerCollision) return;
    if (TimerFinished(enemy->attackTimer) == 0)
    {
        enemy->entityState = STATE_ATTACKING;
        FacePlayer(player,enemy);
        if (enemy->animation != enemy->attackAnimation)
        {
            enemy->animation = enemy->attackAnimation;
            TakeDamage(player,1);
        } 
        
        return;
    }
}

void UpdateCharacterPosition(Character* character)
{
    character->Postion.x += character->speed.x;
    character->Postion.y += character->speed.y;
    character->collisionRect.x = character->Postion.x + (character->animation->frameWidth/2.0f) - 10;
    character->collisionRect.y = character->Postion.y + (character->animation->texture.height/2.0f) - 10;
}

void HandlePlayerAttack(Character* player, Character* enemies)
{
    if (player == NULL) return;
    if (player->entityState == STATE_DEAD) return;
    if (IsKeyPressed(KEY_ENTER) && player->entityState != STATE_ATTACKING)
    {
        if (player->animation != player->attackAnimation) player->animation = player->attackAnimation;
        player->entityState = STATE_ATTACKING;
        player->speed = (Vector2){0,0};

        for (int i = 0; i < ENEMIES_IN_LEVEL_ONE; i++)
        {
            if (CheckCollisionRecs(player->collisionRect, enemies[i].collisionRect) && enemies[i].entityState != STATE_HURT)
            {
                TakeDamage(&enemies[i],5);
            }
        }
    }
    
    return;
}

/*
    Damage Functions:
        - 2 functions have to be done one for the player and another for the enemies.
        

*/
void TakeDamage(Character* character, int damage)
{
    if (character == NULL) return;
    
    if (character->entityState == STATE_HURT) return;
    character->entityState = STATE_HURT;
    character->health -= damage;

    if (character->health <= 0)
    {
        character->entityState = STATE_DEAD;
       if (character->animation != character->deathAnimation) character->animation = character->deathAnimation;
    }

    else
    {
        if (character->animation != character->hurtAnimation) character->animation = character->hurtAnimation;
    }

}