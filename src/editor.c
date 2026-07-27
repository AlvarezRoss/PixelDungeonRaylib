#include "editor.h"


void InitEditor(Rectangle window,TileSet* tileSet) // We pass the window rectangle by value since we don't actually want to change its value
{
    if (tileSet == NULL) return;
    ClearBackground((Color){37,19,26,255});
    Rectangle mainPanel;
    Rectangle sidePanel;
    GetEidtorPanels(window,&sidePanel,&mainPanel,0.2f);
    DrawRectangleRec(sidePanel,(Color){51,0,0,255});
    DrawRectangleRec(mainPanel, (Color){0,0,51,255});
    DrawTileSelector(&sidePanel,tileSet);
    return;
}

void GetEidtorPanels(Rectangle window, Rectangle* sidePanel, Rectangle* mainPanel, float sidePanelPosition)
{
    sidePanel->width = window.width * sidePanelPosition;
    sidePanel->height = window.height;
    sidePanel->x = window.x;
    sidePanel->y = window.y;

    mainPanel->width = window.width * (1-sidePanelPosition);
    mainPanel->height = window.height;
    mainPanel->x = window.x + sidePanel->width;
    mainPanel->y = window.y;
}

void DrawTileSelector(Rectangle* sidePanel, TileSet* tileSet)
{
    if (tileSet == NULL) return;
    int columns = 10; // 8 columns for the grid

    float tileSize = sidePanel->width / (float)columns;

    for (int i = 0; i < TOTAL_TILES; i++)
    {
        int row = i / columns;
        int col = i % columns;
        Rectangle tile = {sidePanel->x + col * tileSize,sidePanel->y + row*tileSize,tileSize,tileSize};
        DrawRectangleRec(tile,(Color){0,0,102,255});
        Rectangle src = {TILESIZE*col,TILESIZE*row,TILESIZE,TILESIZE};
        DrawTexturePro(tileSet->map,src,tile,(Vector2){0,0},0,WHITE);
        DrawRectangleLinesEx(tile,1,(Color){0,0,51,255});
    }
}