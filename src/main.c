
#include "helper.h"
#include "map.h"

int InitPlayer(Character* player);
void DeinitPlayer(Character* player);
void PlayerMovement(Character* player);
void EnemyMovement(Character* enemy, Character* player);
int InitEnemy(Character* enemy, char* enemyType);
void EnemyAttack(Character* enemy);
void UpdateCharacterPosition(Character* character);

int main(void)
{
    Rectangle window = {0,0,480,950};    
    InitWindow(window.height,window.width,"My first Window");

    TileSet* tileSet = malloc(sizeof(TileSet));
    Character player;
    Character enemy;
    LevelData levelData;
    levelData.initPosition = (Vector2){300,300};
    if (InitPlayer(&player) != 0) return 1;
    if (InitEnemy(&enemy,"orc") != 0) return 1;
    if (InitiTileSet(tileSet) != 0) return 1;


    player.Postion.y = enemy.Postion.y;
    player.Postion.x = enemy.Postion.x + 100;

    SetTargetFPS(60);

    while(!WindowShouldClose())
    {
        PlayerMovement(&player);
        UpdateCharacterAnimation(&player);
        UpdateCharacterPosition(&player);
        HandleCharacterRotation(&player);
        HandleGroundCollision(&levelData,tileSet,&player);

        EnemyMovement(&enemy, &player);
        UpdateCharacterAnimation(&enemy);
        HandleCharacterRotation(&enemy);
        
        //-----------------------------------------------------------
        //                Draw
        //-----------------------------------------------------------
        
        BeginDrawing();
            ClearBackground((Color){37,19,26,255});
            DrawText("My first text",20,20,10,WHITE);
            DrawGroundLayer(&levelData,tileSet);
            DrawTextureRec(player.animation->texture,player.animation->frameRect,player.Postion,WHITE);
            DrawTextureRec(enemy.animation->texture,enemy.animation->frameRect,enemy.Postion,WHITE);
            DrawRectangleLinesEx(player.collisionRect,3.5f,WHITE);
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
    if (GetKeyPressed() == 0 && !player->attacking)
    {
        player->walking = false;
        if (player->animation != player->idleAnimation) player->animation = player->idleAnimation;
    }
    // MOVEMENT
    if (IsKeyDown(KEY_A) && !player->attacking)
    {
        if (player->animation != player->walkingAnimation) player->animation = player->walkingAnimation;
        player->walking = true;
        player->speed.x = -1;
        if (!player->rotated) player->rotated = true;
    }
    else if (IsKeyDown(KEY_D) && !player->attacking)
    {
        if (player->animation != player->walkingAnimation) player->animation = player->walkingAnimation;
        player->walking = true;
        player->speed.x = 1;
        if (player->rotated) player->rotated = false;
    }
    else
    {
        player->speed.x = 0;
    }


    if (IsKeyDown(KEY_W) && !player->attacking)
    {
        if (player->animation != player->walkingAnimation) player->animation = player->walkingAnimation;
        player->walking = true;
        player->speed.y = -1;
    }
    else if (IsKeyDown(KEY_S) && !player->attacking)
    {
        if (player->animation != player->walkingAnimation) player->animation = player->walkingAnimation;
        player->walking = true;
        player->speed.y = 1;
    }
    else
    {
        player->speed.y = 0;
    }

    // ATTACK

    if (IsKeyDown(KEY_ENTER) && !player->attacking)
    {
        if (player->animation != player->attackAnimation) player->animation = player->attackAnimation;
        player->walking = false;
        player->attacking = true;
        player->speed = (Vector2){0,0};
    }
    player->collisionRect.x = player->Postion.x;
    player->collisionRect.y = player->Postion.y;
}

// TODO - NEEDS TO ACCOUNT FOR Y MOVEMENT NOW
void EnemyMovement(Character* enemy, Character* player)
{
    if (enemy == NULL || player == NULL) return;

    if (!enemy->playerDetected) 
    {
        if (enemy->animation != enemy->idleAnimation) enemy->animation = enemy->idleAnimation;
    }

    if (enemy->attacking) EnemyAttack(enemy);
    else if (!enemy->attacking)
    {
        if (player->Postion.x - SPRITELEN > enemy->Postion.x)
        {
            enemy->Postion.x += 1;
            enemy->walking = true;
            
            if (enemy->animation != enemy->walkingAnimation)
            {
                enemy->animation = enemy->walkingAnimation;
            } 
            if (enemy->rotated) enemy->rotated = false;
        }
        else if (player->Postion.x + SPRITELEN < enemy->Postion.x)
        {
            enemy->Postion.x -= 1;
            enemy->walking = true;
            
            if (enemy->animation != enemy->walkingAnimation)
            {
                enemy->animation = enemy->walkingAnimation;
            } 
            
            if (!enemy->rotated) enemy->rotated = true;
        }
        else
        {
            enemy->attacking = true;
            enemy->walking = false;
            EnemyAttack(enemy);
        }
    }
}

void EnemyAttack(Character* enemy)
{
    if (enemy == NULL) return;

    if (enemy->animation != enemy->attackAnimation) enemy->animation = enemy->attackAnimation;
}

void UpdateCharacterPosition(Character* character)
{
    character->Postion.x += character->speed.x;
    character->Postion.y += character->speed.y;
}