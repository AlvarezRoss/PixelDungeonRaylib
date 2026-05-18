#include "map.h"

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