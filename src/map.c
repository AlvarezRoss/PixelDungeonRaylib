#include "map.h"

ELEMENT_TYPE groundLayerMatrix[MAPWIDTH][MAPLEN] = 
                                        {
                                        {7,4,4,4,4,4,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //26
                                        {7,3,3,3,3,3,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                        {7,3,3,3,3,3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,0,0,0,0},
                                        {7,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,6,0,0,0},
                                        {7,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,6,0,0,0},
                                        {7,3,3,3,3,3,4,4,4,4,4,4,4,4,4,4,3,3,4,4,4,4,0,0,0,0},
                                        {7,3,3,3,3,3,6,0,0,0,0,0,0,0,0,7,3,3,6,0,0,0,0,0,0,0},
                                        {0,5,5,5,5,5,0,0,0,0,0,0,0,0,0,7,3,3,6,0,0,0,0,0,0,0},
                                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,3,3,6,0,0,0,0,0,0,0},
                                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,3,3,6,0,0,0,0,0,0,0},
                                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,3,3,6,0,0,0,0,0,0,0},
                                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,3,3,6,0,0,0,0,0,0,0},
                                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,3,3,4,4,4,4,4,4,4,0},
                                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,3,3,3,3,3,3,3,3,3,6},
                                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,3,3,3,3,3,3,3,3,3,6},
                                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,3,3,4,4,4,4,4,4,4,0},
                                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,3,3,6,0,0,0,0,0,0,0},
                                        {0,0,0,0,0,7,4,4,4,4,4,4,4,4,4,4,3,3,4,4,4,4,4,0,0,0},
                                        {0,0,0,0,0,7,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,6,0,0},
                                        {0,0,0,0,0,7,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,6,0,0},
                                        {0,0,0,0,0,7,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,6,0,0},
                                        {0,0,0,0,0,7,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,6,0,0},
                                        {0,0,0,0,0,7,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,6,0,0},
                                        {0,0,0,0,0,7,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,6,0,0},
                                        {0,0,0,0,0,0,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,0,0,0}
                                        };

ELEMENT_TYPE objectLayer[MAPWIDTH][MAPLEN] =
                                    {
                                        {0,9,0,9,0,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                        {0,0,0,0,0,0,0,0,9,0,0,9,0,0,0,9,0,0,0,0,0,0,0,0,0,0},
                                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                        {0,0,0,0,0,0,0,0,0,0,10,0,0,0,0,0,8,0,0,0,0,0,0,0,0,0},
                                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
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
// TODO: I need to refactor this logic. DrawObjectLayer should only draw the layer not act as handler for player interaction
void DrawObjectLayer(LevelData* levelData, TileSet* tileSet, Character* player)
{
    if (levelData == NULL || tileSet == NULL) return;
    Vector2 currentPosition = levelData->initPosition;
    for (int i = 0; i < MAPWIDTH; i++)
    {
        currentPosition.x = levelData->initPosition.x;
        for (int g = 0; g < MAPLEN; g++)
        {
            Element element;
            switch (objectLayer[i][g])
            {
            case CHEST:
                element.type = CHEST;
                element.src = (Rectangle){TILESIZE,TILESIZE*8,TILESIZE,TILESIZE};
                break;
            case TORCH:
                element.type = TORCH;
                element.src = (Rectangle){0,TILESIZE*9,TILESIZE,TILESIZE};
                break;
            case BANNER:
                element.type = BANNER;
                element.src = (Rectangle){TILESIZE*4,TILESIZE*7,TILESIZE,TILESIZE};
                break;
            case KEY:
                element.type = KEY;
                element.src = (Rectangle){TILESIZE*9,TILESIZE*9,TILESIZE,TILESIZE};
                break;
            default:
                currentPosition.x += TILESIZE;
                continue;
            }
            element.dest = (Rectangle){currentPosition.x,currentPosition.y,TILESIZE,TILESIZE};
            DrawTexturePro(tileSet->map,element.src,element.dest,(Vector2){0,0},0.0f,WHITE);
            HandlePlayerInteraction(&element,player,i,g);
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
            element.dest = (Rectangle){currentPosition.x,currentPosition.y,TILESIZE,TILESIZE};
            currentPosition.x += TILESIZE;

            bool collisionObject = CheckCollisionObject(i,g);
            if (!collisionObject) continue;
            
            bool collision = CheckCollisionRecs(element.dest,character->collisionRect);
            if (collision) HandleCollisionDirection(&element,character);
        }
        currentPosition.y += TILESIZE;
        
    }

}

void HandleCollisionDirection(Element* element, Character* character)
{
    if (!element || !character) return;

    Rectangle collisionBox = {0};

    collisionBox = GetCollisionRec(element->dest,character->collisionRect);
    // we need the center points of both the element and the character to then compare them and that way determine the direction of the collision
    Vector2 characterCenter = (Vector2){character->collisionRect.x/2.0f, character->collisionRect.y/2.0f};
    Vector2 elementCenter = (Vector2){element->dest.x/2.0f, element->dest.y/2.0f};

    // Checking if the collision is horizontal
    /* We add or subtract the collision width/height to the position to move the player away from the collision point
        and to make a wobbeling motion when a collision happens
    */
    if (collisionBox.width < collisionBox.height)
    {
        if (elementCenter.x < characterCenter.x) character->Postion.x += collisionBox.width;// collision from the left
        else if (elementCenter.x > characterCenter.x) character->Postion.x -= collisionBox.width; // collision from the right
       
        character->speed.x = 0.0f;
    }
    else
    {
        if (elementCenter.y < characterCenter.y) character->Postion.y += collisionBox.height;
        else if (elementCenter.y > characterCenter.y) character->Postion.y -= collisionBox.height;

        character->speed.y = 0.0f;
    }

    return;
}
void HandlePlayerInteraction(Element* element, Character* player, int x, int y)
{
    if (element == NULL || player == NULL) return;
    if (!IsKeyPressed(KEY_E)) return;

    switch (element->type)
    {
    case CHEST:
        objectLayer[x][y] = 11;
        break;
    case KEY:
        objectLayer[x][y] = 0;
        break;
    default:
        break;
    }

    return;
}

bool CheckCollisionObject(int x, int y)
{
    switch (groundLayerMatrix[x][y])
    {
            case WALL_FRONT:
            case WALL_SIDE:
            case WALL_BACK:
            case WALL_SIDE_LEFT:
                return true;            
            case NONE:
            default:
                return false;
    }

    return false;
}
