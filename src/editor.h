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
    int currentEntityCount;
    float mapSize;
    EditorState state;
    TileSet* tileSet;
    TileSet* entityTile;
    Rectangle mainPanel;
    Rectangle sidePanel;
    float mainPanelPosition;
    Character entities[MAXENTITIES];
}MapEditor;

int InitEditor(TileSet* tileSet,MapEditor* mapEditor, float mainPanelPosition);
int InitEntityTileset(MapEditor* mapEditor);
void ProcessEditor(MapEditor* mapEditor,Rectangle window);
void GetEidtorPanels(Rectangle window, MapEditor* mapEditor);
void DrawTileSelector(MapEditor* mapEditor);
void DrawEntitySelector(MapEditor* mapEditor);
void HandleTileSelection(Rectangle* tile, int tileIndex, MapEditor* editor);
void DrawMainPanel(MapEditor* mapEditor);
void HandlePlaceTile(MapEditor* mapEditor, int x, int y, Rectangle* tile);
void HandleSelectLayer(MapEditor *mapEditor);
void DeinitEditor(MapEditor* MapEditor);
#endif