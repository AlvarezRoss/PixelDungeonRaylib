
#include "helper.h"
#include "map.h"
#include "enemyBehaviours.h"
#include "editor.h"


void PlayerMovement(Character* player);
void EnemyMovement(Character* enemy, Character* player);
void EnemyAttack(Character* enemy, Character* player);
void UpdateCharacterPosition(Character* character);
void HandlePlayerAttack(Character* player, Character* enemies);
void TakeDamage(Character* character, int damage);
void ProcTestGameLoop(Character* player, Character* enemies, LevelData* levelData, TileSet* tileSet, Camera2D* camera);
void DrawTestGameLoop(Camera2D* camera, LevelData* levelData, TileSet* tileSet, Character* player, Character* enemies);
void DrawCustomMapLoop(Camera2D* camera, MapEditor* mapEditor, GameState* gameState, Rectangle window);
void ProcessCustomMapLoop(Camera2D* camera, MapEditor* mapEditor, GameState* gameState,Rectangle window);

int main(void)
{
    Rectangle window = {0,0,WINDOWED_MODE_SIZE,WINDOWED_MODE_SIZE};    
    InitWindow(window.height,window.width,"My first Window");
    Graphics knightGraphics;
    Graphics orcGraphics;
    Graphics skelletonGraphics;
    InitGraphics(&knightGraphics,ENTITY_PLAYER);
    InitGraphics(&orcGraphics,ENTITY_ORC);
    InitGraphics(&skelletonGraphics,ENTITY_SKELLETON);
    TileSet* tileSet = malloc(sizeof(TileSet));
    Character player;
    Character enemies[ENEMIES_IN_LEVEL_ONE];
    LevelData levelData;
    levelData.initPosition = (Vector2){300,300};
    if (InitPlayer(&player,&knightGraphics,(float)levelData.initPosition.x + 20,(float)levelData.initPosition.y -20) != 0) return 1;
    if (InitiTileSet(tileSet) != 0) return 1;

    if (InitEnemy(&enemies[0],ENTITY_ORC,&orcGraphics,(float)levelData.initPosition.x +30,(float)levelData.initPosition.y-10) != 0) return 1;

    Camera2D camera = {0};
    if (InitCamera(&camera,&player,window) != 0) return 1;

    GameState gameState;
    if(InitGameState(&gameState) != 0) return 1;
    SetTargetFPS(gameState.targetFps);

    MapEditor editor;
    InitEditor(tileSet,&editor,0.2f);

    while(!WindowShouldClose())
    {
        if(IsKeyPressed(KEY_F1)) FullScreen(&window.width,&window.height,&camera);
        GameStateInputHandle(&gameState);
        if (gameState.State == GAME_STATE_RUNNING)
        {
            ProcTestGameLoop(&player,enemies,&levelData,tileSet,&camera);
        }
        else if (gameState.State == GAME_STATE_RUNNING_CUSTOM_MAP)
        {
            ProcessCustomMapLoop(&camera,&editor,&gameState, window);
        }
        
        //-----------------------------------------------------------
        //                Draw
        //-----------------------------------------------------------
        
        BeginDrawing();
            switch (gameState.State)
            {
            case GAME_STATE_RUNNING:
                DrawTestGameLoop(&camera,&levelData,tileSet,&player,enemies);
                break;
            case GAME_STATE_IN_EDITOR:
                ProcessEditor(&editor,&window);
                break;
            case GAME_STATE_UNINITIALIZED_CUSTON_MAP:
                InitCustomMap(&gameState,&editor,&knightGraphics,&orcGraphics,&skelletonGraphics);
                break;
            case GAME_STATE_RUNNING_CUSTOM_MAP:
                DrawCustomMapLoop(&camera,&editor,&gameState,window);

                break;
            case GAME_STATE_PAUSED:
            default:
                break;
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
    DeinitEditor(&editor);
    DeinitGraphics(&knightGraphics);
    DeinitGraphics(&orcGraphics);
    DeinitGraphics(&skelletonGraphics);
    CloseWindow();
    
    return 0;    
}

void ProcTestGameLoop(Character* player, Character* enemies, LevelData* levelData, TileSet* tileSet, Camera2D* camera)
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
void DrawTestGameLoop(Camera2D* camera, LevelData* levelData, TileSet* tileSet, Character* player, Character* enemies)
{
    ClearBackground((Color){37,19,26,255});        
    BeginMode2D(*camera);
        DrawGroundLayer(levelData,tileSet);
        DrawObjectLayer(levelData,tileSet,player); // for now I need to pass the a player pointer... PENDING REFACTOR
       // DrawTextureRec(enemies[0].animation->texture,enemies[0].animation->frameRect,enemies[0].Postion,WHITE);
       // DrawTextureRec(player->animation->texture,player->animation->frameRect,player->Postion,WHITE);

       DrawTextureRec(enemies[0].animation->texture,HandleCharacterRotation(&enemies[0]),enemies[0].Postion,WHITE);
       DrawTextureRec(player->animation->texture,HandleCharacterRotation(player),player->Postion,WHITE);
    EndMode2D();
}
/*
    We use different init functions for the player and the enemies to handle the specefic paths to the different animation sprites
*/

void PlayerMovement(Character* player)
{
    if (player == NULL) return;
    if (player->entityState == STATE_DEAD) return;
    if (player->entityState == STATE_HURT) return;
    // IDLE
    if (GetKeyPressed() == 0 && player->entityState != STATE_ATTACKING)
    {
        player->entityState = STATE_IDLE;
        if (player->animation != player->graphics->idleAnimation) player->animation = player->graphics->idleAnimation;
    }
    // MOVEMENT
    if (IsKeyDown(KEY_A) && player->entityState != STATE_ATTACKING)
    {
        if (player->animation != player->graphics->walkingAnimation) player->animation = player->graphics->walkingAnimation;
        player->entityState = STATE_WALKING;
        player->speed.x = -1;
        if (!player->rotated) player->rotated = true;
    }
    else if (IsKeyDown(KEY_D) && player->entityState != STATE_ATTACKING)
    {
        if (player->animation != player->graphics->walkingAnimation) player->animation = player->graphics->walkingAnimation;
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
        if (player->animation != player->graphics->walkingAnimation) player->animation = player->graphics->walkingAnimation;
        player->entityState = STATE_WALKING;
        player->speed.y = -1;
    }
    else if (IsKeyDown(KEY_S) && player->entityState != STATE_ATTACKING)
    {
        if (player->animation != player->graphics->walkingAnimation) player->animation = player->graphics->walkingAnimation;
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
        if (enemy->animation != enemy->graphics->idleAnimation) enemy->animation = enemy->graphics->idleAnimation;
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
        if (enemy->animation != enemy->graphics->attackAnimation)
        {
            enemy->animation = enemy->graphics->attackAnimation;
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
        if (player->animation != player->graphics->attackAnimation) player->animation = player->graphics->attackAnimation;
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
       if (character->animation != character->graphics->deathAnimation) character->animation = character->graphics->deathAnimation;
    }

    else
    {
        if (character->animation != character->graphics->hurtAnimation) character->animation = character->graphics->hurtAnimation;
    }

}

void DrawCustomMapLoop(Camera2D* camera, MapEditor* mapEditor, GameState* gameState, Rectangle window)
{
    InitCamera(camera,mapEditor->player,window);
    BeginMode2D(*camera);
        DrawCustomMap(mapEditor,gameState,window);
        DrawCustomMapEntities(mapEditor);
    EndMode2D();
}


void ProcessCustomMapLoop(Camera2D* camera, MapEditor* mapEditor, GameState* gameState, Rectangle window)
{
    if (camera == NULL || mapEditor == NULL || gameState == NULL) return;
    if (gameState->State != GAME_STATE_RUNNING_CUSTOM_MAP) return;
    for (int i = 0; i < mapEditor->entityCount; i++)
    {
        if (mapEditor->entities[i].entityState == STATE_INACTIVE) continue;

        if (mapEditor->entities[i].entityType == ENTITY_PLAYER)
        {
            PlayerMovement(mapEditor->player);
            HandlePlayerAttack(mapEditor->player,mapEditor->entities);
            UpdateCharacterCamera(camera,mapEditor->player);
            HandlePlayerInteraction(mapEditor->player,mapEditor);
        }
        else
        {
            EnemyMovement(&mapEditor->entities[i], mapEditor->player);
            EnemyAttack(&mapEditor->entities[i], mapEditor->player);
        }

        UpdateCharacterAnimation(&mapEditor->entities[i]);
        UpdateCharacterPosition(&mapEditor->entities[i]);
        HandleCustomMapCollision(mapEditor,&mapEditor->entities[i],window);
    }
}