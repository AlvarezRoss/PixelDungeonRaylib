#ifndef MAP_H
#define MAP_H

#include "helper.h"

#define TILESIZE 16


typedef struct TileSet
{
    Image tileSetImage;
    Texture2D map;
    Rectangle tileMapSize;
}TileSet;



int InitiTileSet(TileSet* tileSet);
void DeInitTileSet(TileSet* tileSet);
void DrawRoom(TileSet* tileSet, Vector2 position);


#endif