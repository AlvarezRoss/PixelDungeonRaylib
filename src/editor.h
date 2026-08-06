#ifndef EDITOR_H
#define EDITOR_H

#include "helper.h"
#include "map.h"
#define MAXENTITIES 255
typedef enum EditorState
{
    EDITOR_STATE_PAINTING,
    EDITOR_STATE_ERRASING
}EditorState;
typedef struct MapEditor
{
    int selectedTileIndex;
    int selectedMapIndex;
    int map[3][MAPWIDTH][MAPLEN];
    int drawLayer;
    int entityCount;
    float mapSize;
    EditorState state;
    TileSet* tileSet;
    TileSet* entityTile;
    Rectangle mainPanel;
    Rectangle sidePanel;
    float mainPanelPosition;
    Character entities[MAXENTITIES];
    bool playerInGame;
    Character* player;
}MapEditor;

int InitEditor(TileSet* tileSet,MapEditor* mapEditor, float mainPanelPosition);
int InitEntityTileset(MapEditor* mapEditor);
void ProcessEditor(MapEditor* mapEditor,Rectangle* window);
void GetEidtorPanels(Rectangle window, MapEditor* mapEditor);
void DrawTileSelector(MapEditor* mapEditor);
void DrawEntitySelector(MapEditor* mapEditor);
void HandleTileSelection(Rectangle* tile, int tileIndex, MapEditor* editor);
void DrawMainPanel(MapEditor* mapEditor);
void HandlePlaceTile(MapEditor* mapEditor, int x, int y, Rectangle* tile);
void HandleSelectLayer(MapEditor *mapEditor);
void DeinitEditor(MapEditor* MapEditor);
void AddEntity(MapEditor* mapEditor, int x, int y);
int InitCustomMap(GameState* gameState, MapEditor* mapEditor, Graphics* knightGraphics, Graphics* orcGraphics, Graphics* skelletonGraphics);
void DrawCustomMap(MapEditor* mapEditor, GameState* gameState, Rectangle window);
void DrawCustomMapEntities(MapEditor* mapEditor);
void HandleCustomMapCollision(MapEditor* mapEditor, Character* entity, Rectangle window);
bool IsCollisionObject(int index);
#endif