#include "editor.h"

/*
    Function call when the game begins after loading the tileset in memory.
    It sets the position of the main pannel as a percet pont (0.2f) in this case
    It also sets the entire map array to -1 which will make the draw function ignore it - see below
*/
int InitEditor(TileSet* tileSet,MapEditor* mapEditor, float mainPanelPosition)
{
    if (tileSet == NULL || mapEditor == NULL) return -1;
    mapEditor->tileSet = tileSet;
    mapEditor->mainPanelPosition = mainPanelPosition;
    memset(&mapEditor->map,-1,sizeof(mapEditor->map));
    memset(&mapEditor->entities,-1,sizeof(mapEditor->entities));
    mapEditor->currentEntityCount = 0;
    mapEditor->drawLayer = 0; // draws on the first layer
    mapEditor->entityTile = malloc(sizeof(TileSet));
    if (InitEntityTileset(mapEditor) < 0) return -1;

    return 0;
}

int InitEntityTileset(MapEditor* mapEditor)
{
    if (mapEditor == NULL) return -1;

    mapEditor->entityTile->tileSetImage = LoadImage("Assets/CharacterSelector16x16.png");
    if (mapEditor->entityTile->tileSetImage.data == NULL) return -1;

    mapEditor->entityTile->map = LoadTextureFromImage(mapEditor->entityTile->tileSetImage);
    UnloadImage(mapEditor->entityTile->tileSetImage);

    if (mapEditor->entityTile->map.id == 0) return -1;
    mapEditor->entityTile->tileMapSize = (Rectangle){0,0,90,20};
    return 0;
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
    DrawMainPanel(mapEditor);
    if (mapEditor->drawLayer == 2) DrawEntitySelector(mapEditor);
    else DrawTileSelector(mapEditor);
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

void DrawEntitySelector(MapEditor* mapEditor)
{
    if (mapEditor == NULL) return;

    int columns = 3;
    float tileSize = mapEditor->sidePanel.width/(float)columns;

    for (int i = 0; i < ENTITY_TOTAL; i++)
    {
        int row = i / columns;
        int col = i % columns;
        Rectangle tile = {mapEditor->sidePanel.x + col * tileSize,mapEditor->sidePanel.y + row*tileSize,tileSize,tileSize};
        DrawRectangleRec(tile,(Color){0,0,102,255});
        Rectangle src = {TILESIZE*col,0,TILESIZE,TILESIZE};
        DrawTexturePro(mapEditor->entityTile->map,src,tile,(Vector2){0,0},0,WHITE);
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
    float tileWidth = mapEditor->mainPanel.width/MAPWIDTH;
    float tileLen = mapEditor->mainPanel.height/MAPLEN;  
    float tileSize = fminf(tileWidth,tileLen);
    //float tileSize = mapEditor->mainPanel.width/MAPLEN;
    for (int layer = 0; layer < 3; layer++)
    {
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
                HandleSelectLayer(mapEditor);
                //if (mapEditor->drawLayer != 3)
                HandlePlaceTile(mapEditor,g,i,&tile);

                DrawRectangleLinesEx(tile,1,(Color){0,0,102,255});
                if(mapEditor->map[layer][i][g] != -1) 
                {
                    if(layer != 2) DrawTexturePro(mapEditor->tileSet->map,GetTileSrcRect(mapEditor->map[layer][i][g]),tile,(Vector2){0,0},0,WHITE);
                    else DrawTexturePro(mapEditor->entityTile->map,GetTileSrcRect(mapEditor->map[layer][i][g]),tile,(Vector2){0,0},0,WHITE);
                }    
            }
        }
    }
}

void HandlePlaceTile(MapEditor* mapEditor, int x, int y, Rectangle* tile)
{
    if(CheckCollisionPointRec(GetMousePosition(), *tile) && IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        mapEditor->map[mapEditor->drawLayer][y][x] = mapEditor->selectedTileIndex;
        printf("Tile of layer: %d in position x: %d , y: %d is -> %d \n",mapEditor->drawLayer,x,y,mapEditor->selectedTileIndex);
        return;
    }
    if(CheckCollisionPointRec(GetMousePosition(), *tile) && IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
    {
        mapEditor->map[mapEditor->drawLayer][y][x] = -1;
        return;
    }
}

// void HandlePlaceEntity(MapEditor* mapEditor, int x, int y, Rectangle* tile)
// {
//     return;
// }

void HandleSelectLayer(MapEditor *mapEditor)
{
    if (mapEditor == NULL) return;

    if (IsKeyDown(KEY_C))
    {
        mapEditor->drawLayer = 0;
        return;
    }
    if (IsKeyDown(KEY_V))
    {
        mapEditor->drawLayer = 1;
        return;
    }
    if (IsKeyDown(KEY_B))
    {
        mapEditor->drawLayer = 2;
        return;
    }
}
void DeinitEditor(MapEditor* MapEditor)
{
    UnloadTexture(MapEditor->entityTile->map);
    free(MapEditor->entityTile);
    MapEditor->entityTile = NULL;
}