#ifndef EDITOR_H
#define EDITOR_H

#include "helper.h"
#include "map.h"
typedef enum EditorState
{
    EDITOR_STATE_PAINTING,
    EDITOR_STATE_ERRASING
}EditorState;
typedef struct MapEditor
{
    int selectedTileIndex;
    int selectedMapIndex;
    int map[2][MAPWIDTH][MAPLEN];
    int drawLayer;
    float mapSize;
    EditorState state;
    TileSet* tileSet;
    Rectangle mainPanel;
    Rectangle sidePanel;
    float mainPanelPosition;
}MapEditor;

void InitEditor(TileSet* tileSet,MapEditor* mapEditor, float mainPanelPosition);
void ProcessEditor(MapEditor* mapEditor,Rectangle window);
void GetEidtorPanels(Rectangle window, MapEditor* mapEditor);
void DrawTileSelector(MapEditor* mapEditor);
void HandleTileSelection(Rectangle* tile, int tileIndex, MapEditor* editor);
void DrawMainPanel(MapEditor* mapEditor);
void HandlePlaceTile(MapEditor* mapEditor, int x, int y, Rectangle* tile);
void HandleSelectLayer(MapEditor *mapEditor);
#endif