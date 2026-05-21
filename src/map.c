#include "map.h"

ELEMENT_TYPE groundLayerMatrix[MAPWIDTH][MAPLEN] = 
                                        {
                                        {7,4,4,4,4,4,6,0,0,0,0,0},
                                        {7,3,3,3,3,3,6,0,0,0,0,0},
                                        {7,3,3,3,3,3,4,4,4,4,4,0},
                                        {7,3,3,3,3,3,3,3,3,3,3,6},
                                        {7,3,3,3,3,3,3,3,3,3,3,6},
                                        {7,3,3,3,3,3,4,4,4,4,4,0},
                                        {7,3,3,3,3,3,6,0,0,0,0,0},
                                        {0,5,5,5,5,5,0,0,0,0,0,0}
                                        };


int InitiTileSet(TileSet* tileSet)
{
  if (tileSet == NULL) return 1;
  
  tileSet->tileSetImage = LoadImage("Assets/Dungeon_Tileset.png");
  if (tileSet->tileSetImage.data == NULL) return 1;

  tileSet->map = LoadTextureFromImage(tileSet->tileSetImage);
  if (tileSet->map.id == 0) return 1;


  tileSet->tileMapSize = (Rectangle){0,0,160,160};

  return 0;
}

void DrawRoom(TileSet* tileSet, Vector2 position)
{
    Rectangle roomSrc = {0,0,TILESIZE*6,TILESIZE*5};
    Rectangle roomDest = {position.x,position.y,TILESIZE*6,TILESIZE*5};

    DrawTexturePro(tileSet->map,roomSrc,roomDest,position,0.0f,WHITE);
}


// Remember to nullify tileSet pointer
void DeInitTileSet(TileSet* tileSet)
{
    if (tileSet == NULL) return;


    UnloadImage(tileSet->tileSetImage);
    UnloadTexture(tileSet->map);
    
    free(tileSet);
}

void DrawGroundLayer(LevelData* levelData, TileSet* tileSet)
{
    if (levelData == NULL || tileSet == NULL) return;
    Vector2 currentPosition = levelData->initPosition;

    for (int i = 0; i < MAPWIDTH; i++)
    {
        currentPosition.x = levelData->initPosition.x;

        for (int g = 0; g < MAPLEN; g++)
        {
            Element element;
            switch (groundLayerMatrix[i][g])
            {
            case WALL_FRONT:
                element.type = WALL_FRONT;
                element.src = (Rectangle){TILESIZE,0,TILESIZE,TILESIZE};
                break;
            case FLOOR:
                element.type = FLOOR;
                element.src = (Rectangle){TILESIZE*6,0,TILESIZE,TILESIZE};
                break;
            case WALL_SIDE:
                element.type = WALL_SIDE;
                element.src = (Rectangle){TILESIZE*5,0,TILESIZE,TILESIZE};
                break;
            case WALL_BACK:
                element.type = WALL_BACK;
                element.src = (Rectangle){TILESIZE,TILESIZE*5,TILESIZE,TILESIZE};
                break;
            case WALL_SIDE_LEFT:
                element.type = WALL_SIDE_LEFT;
                element.src = (Rectangle){0,0,TILESIZE,TILESIZE};
                break;;
            case NONE:
            default:
                currentPosition.x += TILESIZE;
                continue;
            }
            
            element.dest = (Rectangle){currentPosition.x,currentPosition.y,TILESIZE,TILESIZE};

            DrawTexturePro(tileSet->map,element.src,element.dest,(Vector2){0,0},0.0f,WHITE);

            currentPosition.x += TILESIZE;
        }
        currentPosition.y += TILESIZE; 
        
    }
}

void HandleGroundCollision(LevelData* levelData, TileSet* tileSet, Character* character)
{
    if (levelData == NULL || tileSet == NULL || character == NULL) return;
    Vector2 currentPosition = levelData->initPosition;
    Element element;
    for (int i = 0; i < MAPWIDTH; i++)
    {
        currentPosition.x = levelData->initPosition.x;

        for (int g = 0; g < MAPLEN; g++)
        {
            switch (groundLayerMatrix[i][g])
            {
            case WALL_FRONT:
                element.type = WALL_FRONT;
                element.src = (Rectangle){TILESIZE,0,TILESIZE,TILESIZE};
                break;
            case WALL_SIDE:
                element.type = WALL_SIDE;
                element.src = (Rectangle){TILESIZE*5,0,TILESIZE,TILESIZE};
                break;
            case WALL_BACK:
                element.type = WALL_BACK;
                element.src = (Rectangle){TILESIZE,TILESIZE*5,TILESIZE,TILESIZE};
                break;
            case WALL_SIDE_LEFT:
                element.type = WALL_SIDE_LEFT;
                element.src = (Rectangle){0,0,TILESIZE,TILESIZE};
                break;;
            case NONE:
            default:
                currentPosition.x += TILESIZE;
                continue;
            }
            
            element.dest = (Rectangle){currentPosition.x,currentPosition.y,TILESIZE,TILESIZE};

            if (CheckCollisionRecs(element.dest,character->animation->frameRect))
            {
                //printf("Collided!!!");
                character->speed = (Vector2){0,0};
            } 
            else
            {
               // printf("Not collided");
            }

            currentPosition.x += TILESIZE;
        }
        currentPosition.y += TILESIZE; 
        
    }

}
