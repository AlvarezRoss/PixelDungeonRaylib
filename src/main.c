
#include "helper.h"
#include "map.h"

int InitPlayer(Character* player);
void DeinitPlayer(Character* player);
void PlayerMovement(Character* player);
void EnemyMovement(Character* enemy, Character* player);
int InitEnemy(Character* enemy, char* enemyType);
void EnemyAttack(Character* enemy);
void UpdateCharacterPosition(Character* character);
void HandlePlayerAttack(Character* player, Character* enemies);
void TakeDamage(Character* character, int damage);

int main(void)
{
    Rectangle window = {0,0,800,800};    
    InitWindow(window.height,window.width,"My first Window");

    TileSet* tileSet = malloc(sizeof(TileSet));
    Character player;
    Character enemy;
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
    SetTargetFPS(60);
    

    while(!WindowShouldClose())
    {
        PlayerMovement(&player);
        HandleGroundCollision(&levelData,tileSet,&player);
        HandlePlayerAttack(&player,enemies);
        UpdateCharacterAnimation(&player);
        UpdateCharacterPosition(&player);
        HandleCharacterRotation(&player);

        UpdateCharacterCamera(&camera,&player);
        

        EnemyMovement(&enemies[0], &player);
        UpdateCharacterAnimation(&enemies[0]);
        HandleCharacterRotation(&enemies[0]);
        
        //-----------------------------------------------------------
        //                Draw
        //-----------------------------------------------------------
        
        BeginDrawing();
            ClearBackground((Color){37,19,26,255});
            DrawText("My first text",20,20,10,WHITE);
            
            BeginMode2D(camera);
                DrawGroundLayer(&levelData,tileSet);
                DrawObjectLayer(&levelData,tileSet);
                DrawTextureRec(player.animation->texture,player.animation->frameRect,player.Postion,WHITE);
                DrawTextureRec(enemies[0].animation->texture,enemies[0].animation->frameRect,enemies[0].Postion,WHITE);
            EndMode2D();
            
        EndDrawing();
    }

    // ----------------------------------------------------------------
    // DEINIT
    // ----------------------------------------------------------------
    DeinitPlayer(&player);
    DeinitPlayer(&enemy); // Unsure if I need to have another function for enemy characters or just rename the function
    DeInitTileSet(tileSet);
    tileSet = NULL;
    CloseWindow();
    
    return 0;    
}

/*
    We use different init functions for the player and the enemies to handle the specefici paths to the different animation sprites
*/
int InitPlayer(Character* player)
{
    Animation* idleAnimation = malloc(sizeof(Animation));
    Animation* walkingAnimation = malloc(sizeof(Animation));
    Animation* attackAnimation = malloc(sizeof(Animation));
    Animation* hurtAnimation = malloc(sizeof(Animation));

    if (InitAnimation(idleAnimation,"Assets/Characters/Characters(100x100)/Knight/Knight/Knight-Idle.png",6) != 0) return 1;
    if (InitAnimation(walkingAnimation,"Assets/Characters/Characters(100x100)/Knight/Knight/Knight-Walk.png",8) != 0) return 1;
    if (InitAnimation(attackAnimation,"Assets/Characters/Characters(100x100)/Knight/Knight/Knight-Attack01.png", 7) != 0) return 1;
    if (InitAnimation(hurtAnimation,"Assets/Characters/Characters(100x100)/Knight/Knight/Knight-Hurt.png",4) != 0) return 1;
    if (InitCharacter(player,idleAnimation, walkingAnimation, attackAnimation, hurtAnimation) != 0) return 1;
    player->entityType = ENTITY_PLAYER;
    player->maxHealth = 40;
    player->health = player->maxHealth;
    return 0;
}

int InitEnemy(Character* enemy, char* enemyType)
{
    if (enemy == NULL || enemyType == NULL) return 1;
    //if (strcmp(enemyType,"") != 0) return 1;

    Animation* idleAnimation = malloc(sizeof(Animation));
    Animation* walkAnimation = malloc(sizeof(Animation));
    Animation* attackAnimation = malloc(sizeof(Animation));
    Animation* hurtAnimation = malloc(sizeof(Animation));

    // TODO -- ENEMY TYPES!!!

    if (InitAnimation(idleAnimation,"Assets/Characters/Characters(100x100)/Orc/Orc/Orc-Idle.png",6) != 0) return 1;
    if (InitAnimation(walkAnimation,"Assets/Characters/Characters(100x100)/Orc/Orc/Orc-Walk.png",8) != 0) return 1;
    if (InitAnimation(attackAnimation,"Assets/Characters/Characters(100x100)/Orc/Orc/Orc-Attack01.png",6) != 0) return 1;
    if (InitAnimation(hurtAnimation,"Assets/Characters/Characters(100x100)/Orc/Orc/Orc-Hurt.png",4) != 0) return 1;
    if (InitCharacter(enemy,idleAnimation,walkAnimation,attackAnimation,hurtAnimation) != 0) return 1;

    enemy->playerDetected = true;
    enemy->entityType = ENTITY_ORC;

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
}

void PlayerMovement(Character* player)
{
    if (player == NULL) return;
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

    if (!enemy->playerDetected || enemy->entityState == STATE_IDLE) // Revise -> not detecing a player should change the state to idle
    {
        if (enemy->animation != enemy->idleAnimation) enemy->animation = enemy->idleAnimation;
    }
    if (enemy->entityState == STATE_HURT) return;

    if (enemy->entityState == STATE_ATTACKING) EnemyAttack(enemy);
    
    
}

void EnemyAttack(Character* enemy) // TODO- IMPLEMENTING HIT LOGIC
{
    if (enemy == NULL) return;

    if (enemy->animation != enemy->attackAnimation) enemy->animation = enemy->attackAnimation;
}

void UpdateCharacterPosition(Character* character)
{
    character->Postion.x += character->speed.x;
    character->Postion.y += character->speed.y;
}

void HandlePlayerAttack(Character* player, Character* enemies)
{

    if (IsKeyPressed(KEY_ENTER) && player->entityState != STATE_ATTACKING)
    {
        if (player->animation != player->attackAnimation) player->animation = player->attackAnimation;
        player->entityState = STATE_ATTACKING;
        player->speed = (Vector2){0,0};

        for (int i = 0; i < ENEMIES_IN_LEVEL_ONE; i++)
        {
            if (CheckCollisionRecs(player->collisionRect, enemies[i].collisionRect) && enemies[i].entityState != STATE_HURT)
            {
                enemies[i].entityState = STATE_HURT;
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
    
    if (character->entityState != STATE_HURT || damage == 0) return;


    if (character->animation != character->hurtAnimation) character->animation = character->hurtAnimation;
    character->health -= damage;
}