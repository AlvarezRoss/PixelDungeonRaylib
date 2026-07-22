#ifndef MAP_H
#define MAP_H

#include "helper.h"

#define TILESIZE 16
#define MAPWIDTH 25
#define MAPLEN 26


typedef struct TileSet
{
    Image tileSetImage;
    Texture2D map;
    Rectangle tileMapSize;
}TileSet;

typedef enum ELEMENT_TYPE
{
    NONE,
    DOOR_FRONT,
    CORRIDOR,
    FLOOR,
    WALL_FRONT,
    WALL_BACK,
    WALL_SIDE,
    WALL_SIDE_LEFT,
    CHEST,
    TORCH,
    BANNER,
    KEY
    
}ELEMENT_TYPE;

typedef struct Element
{
    int initalX;
    int finalX;
    int initalY;
    int finalY;
    ELEMENT_TYPE type;
    Rectangle src;
    Rectangle dest;
}Element;

typedef struct LevelData{
    int enemyNumber;
    Vector2 initPosition;
    Character* player;
    Character* enemies;
    
}LevelData;


int InitiTileSet(TileSet* tileSet);
void DeInitTileSet(TileSet* tileSet);
void DrawRoom(TileSet* tileSet, Vector2 position);
void DrawGroundLayer(LevelData* levelData, TileSet* tileSet);
void HandleGroundCollision(LevelData* levelData, TileSet* tileSet, Character* character);
void HandleCollisionDirection(Element* element, Character* character);
void DrawObjectLayer(LevelData* levelData, TileSet* tileSet, Character* player);
void HandlePlayerInteraction(Element* element, Character* player, int x, int y);
bool CheckCollisionObject(int x, int y);

#endif