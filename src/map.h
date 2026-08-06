#ifndef MAP_H
#define MAP_H

#include "helper.h"

#define TILESIZE 16
#define MAPWIDTH 50
#define MAPLEN 50
#define TILESETCOLS 10


typedef struct TileSet
{
    Image tileSetImage;
    Texture2D map;
    Rectangle tileMapSize;
}TileSet;

typedef enum TILES // This is needed for the map editor and the draw and collision logics
{

    // ROW 1 //
    WALL_LEFT_1,
    WALL_FRONT_1,
    WALL_FRONT_2,
    WALL_FRONT_3,
    WALL_FRONT_4,
    WALL_RIGHT_1,
    FLOOR_1,
    FLOOR_2,
    FLOOR_3,
    FLOOR_4,

    // ROW 2 //

    WALL_LEFT_2,
    FLOOR_5,
    FLOOR_6,
    FLOOR_7,
    FLOOR_8,
    WALL_RIGHT_2,
    FLOOR_9,
    FLOOR_10,
    FLOOR_11,
    FLOOR_12,

    // ROW 3 // 
    WALL_LEFT_3,
    FLOOR_13,
    FLOOR_14,
    FLOOR_15,
    FLOOR_16,
    WALL_RIGHT_3,
    FLOOR_17,
    FLOOR_18,
    FLOOR_19,
    FLOOR_20,

    // ROW 4 // 
    WALL_LEFT_4,
    FLOOR_21,
    FLOOR_22,
    FLOOR_23,
    FLOOR_24,
    WALL_RIGHT_4,
    DOOR_FRONT_1,
    DOOR_FRONT_2,
    HATCH_1,
    LADDER_1,

    // ROW 5 //
    LEFT_CORNER_WALL,
    BACK_WALL_1,
    BACK_WALL_2,
    BACK_WALL_3,
    BACK_WALL_4,
    RIGHT_CORNER_WALL,
    RIGHT_DOOR_1,
    LEFT_DOOR_1,
    RIGHT_DOOR_2,
    STONES_1,

    // ROW 6 // 
    TOP_LEFT_CORNER_WALL_1,
    BACK_WALL_5,
    BACK_WALL_6,
    TOP_RIGHT_CORNER_WALL_1,
    TOP_LEFT_CORNER_WALL_2,
    TOP_RIGHT_CORNER_WALL_2,
    RIGHT_DOOR_3,
    LEFT_DOOR_2,
    RIGHT_DOOR_4,
    STONES_2,

    // ROW 7 //
    FLOOR_25,
    FLOOR_26,
    FLOOR_27,
    FLOOR_28,
    WEB_1,
    WEB_2,
    DOOR_FRONT_3,
    DOOR_FRONT_4,
    BONES_1,
    FLOOR_29,

    // ROW 8 //
    FLOOR_30,
    FLOOR_31,
    FLOOR_32,
    FLOOR_33,
    BANNER_1,
    DECOR_1,
    DECOR_2,
    SKULL_1,
    FLOOR_34,
    FLOOR_35,

    // ROW 9 //
    CHEST_1,
    CHEST_2,
    CHEST_3,
    CHEST_4,
    CHEST_5,
    CHEST_6,
    COIN_1,
    MANA_SMALL_1,
    KEY_1,
    HP_BIG,

    //ROW 10//
    TORCH_1,
    TORCH_2,
    TORCH_3,
    TORCH_4,
    TORCH_5,
    TORCH_6,
    TORCH_7,
    MANA_BIG_1,
    HP_SMALL_1,
    KEY_2,


    TOTAL_TILES
}TILES;

typedef enum ELEMENT_TYPE // This is used just for the test map - Use the Tiles enum to make actual maps
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
// Not Really Used...
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
Rectangle GetTileSrcRect(TILES tile);

#endif