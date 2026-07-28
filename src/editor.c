#include "editor.h"

/*
    Function call when the game begins after loading the tileset in memory.
    It sets the position of the main pannel as a percet pont (0.2f) in this case
    It also sets the entire map array to -1 which will make the draw function ignore it - see below
*/
void InitEditor(TileSet* tileSet,MapEditor* mapEditor, float mainPanelPosition)
{
    if (tileSet == NULL || mapEditor == NULL) return;
    mapEditor->tileSet = tileSet;
    mapEditor->mainPanelPosition = mainPanelPosition;
    memset(&mapEditor->map,-1,sizeof(mapEditor->map));

}

/*
    - First it gets the Panels on which we are going to draw our editor based on the current window size -- see function docs below
    - Then we draw to the screen both panels
    - See the documentation for DrawTileSelector and DrawMainPanel below
*/
void ProcessEditor(MapEditor* mapEditor, Rectangle window) // We pass the window rectangle by value since we don't actually want to change its value
{
    if (mapEditor == NULL) return;
    GetEidtorPanels(window,mapEditor);
    ClearBackground((Color){37,19,26,255});
    DrawRectangleRec(mapEditor->sidePanel,(Color){51,0,0,255});
    DrawRectangleRec(mapEditor->mainPanel, (Color){0,0,51,255});
    DrawTileSelector(mapEditor);
    DrawMainPanel(mapEditor);
    return;
}
/*
    It takes the current size of the window
    It calculates the side panel - Since it will be set on the left of the screen
        - It multiples the width of the screen by the position of the main panel (0.2 in this case) which means it will cover 20% of the screen
        - We want to cover the entire screen so we set its height to that of the screen
        - It will be on the left of the screen to the x and y positions are that of window
    It calculates the main panel:
        - It will be set after the side panel and it must cover the rest of the screen that is why we use 1 - 0.2 in this case
        - Same hight as the window
        - The x position must be that on the window + the width of the side panel so it sits to its right.
        - The y position is the same

*/
void GetEidtorPanels(Rectangle window, MapEditor* mapEditor)
{
    mapEditor->sidePanel.width = window.width * mapEditor->mainPanelPosition;
    mapEditor->sidePanel.height = window.height;
    mapEditor->sidePanel.x = window.x;
    mapEditor->sidePanel.y = window.y;

    mapEditor->mainPanel.width = window.width * (1-mapEditor->mainPanelPosition);
    mapEditor->mainPanel.height = window.height;
    mapEditor->mainPanel.x = window.x + mapEditor->sidePanel.width;
    mapEditor->mainPanel.y = window.y;
}
/*
    Pending: Number of columns must not be hardcoded - I could define it when I know how many columns I actually want

    This function does three things:
        - It draws a grid on the side panel.
        - It draws the tiles of the tileset on said grid.
        - Calls a function to set the selected tile inside the mapEditorStruct -- see docs below

    The grid:
        - We get the size of the grid by doing an integer divsion with the width of the side panel by the number of columns.
        - We then need the row and the column we are in now:
            - The row is just the index / number of columns:
                - i = 30 -> 30/10 = 3 -> We are on the fourth row (it starts at 0)
            - The current column is the remainder of diving the index by the number of columns:
                - i = 30 -> 30/10 = 0 with 0 remainder -> We are on column 0
                - i = 35 -> 35/10 = 3 with 5 remainder -> We are on column 5
        - We then create a Tile rectangle with the x position being the initial position of the panel * + the current column * the tilesize
            we do the same thing with the y but insted we multiply it by the row
        - We then draw the grid by calling DrawRectangleLineEx
    Drawing the Tiles:
        - The MapEditor struct has the tile set we are going to draw.
        - We craete a Rectalge with the x position being the Size of the tile * by the current colmun
            and the y position beign the TileSize * by the current row - Meaning that the tile 
*/

void DrawTileSelector(MapEditor* mapEditor)
{
    if (mapEditor == NULL) return;
    int columns = 10;

    float tileSize = mapEditor->sidePanel.width / (float)columns;

    for (int i = 0; i < TOTAL_TILES; i++)
    {
        int row = i / columns;
        int col = i % columns;
        Rectangle tile = {mapEditor->sidePanel.x + col * tileSize,mapEditor->sidePanel.y + row*tileSize,tileSize,tileSize};
        DrawRectangleRec(tile,(Color){0,0,102,255});
        Rectangle src = {TILESIZE*col,TILESIZE*row,TILESIZE,TILESIZE};
        DrawTexturePro(mapEditor->tileSet->map,src,tile,(Vector2){0,0},0,WHITE);
        DrawRectangleLinesEx(tile,1,(Color){0,0,51,255});
        HandleTileSelection(&tile,i,mapEditor);
    }
}

void HandleTileSelection(Rectangle* tile, int tileIndex, MapEditor* mapEditor)
{
    if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) return;

    if (CheckCollisionPointRec(GetMousePosition(),*tile))
    {
        printf("Clicked Tile Number: %d",tileIndex);
        mapEditor->selectedTileIndex = tileIndex;
        return;
    }

    return;
}

void DrawMainPanel(MapEditor* mapEditor)
{
    if (mapEditor == NULL) return;

    float tileSize = mapEditor->mainPanel.width/MAPLEN;
    for(int i = 0; i < MAPWIDTH; i++)
    {
        for(int g = 0; g < MAPLEN; g++)
        {
            Rectangle tile = {
                mapEditor->mainPanel.x + g * tileSize,
                mapEditor->mainPanel.y + i * tileSize,
                tileSize,
                tileSize
            };
            
            HandlePlaceTile(mapEditor,g,i,&tile);
            DrawRectangleLinesEx(tile,1,(Color){0,0,102,255});
            if(mapEditor->map[i][g] != -1) DrawTexturePro(mapEditor->tileSet->map,GetTileSrcRect(mapEditor->map[i][g]),tile,(Vector2){0,0},0,WHITE);
        }
    }
}

void HandlePlaceTile(MapEditor* mapEditor, int x, int y, Rectangle* tile)
{
    if(CheckCollisionPointRec(GetMousePosition(), *tile) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        mapEditor->map[y][x] = mapEditor->selectedTileIndex;
        printf("Tile in position x: %d , y: %d is -> %d \n",x,y,mapEditor->selectedTileIndex);
        return;
    }
    if(CheckCollisionPointRec(GetMousePosition(), *tile) && IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
    {
        mapEditor->map[y][x] = -1;
        return;
    }
}