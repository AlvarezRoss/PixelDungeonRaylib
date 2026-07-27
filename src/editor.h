#ifndef EDITOR_H
#define EDITOR_H

#include "helper.h"
#include "map.h"

void InitEditor(Rectangle window, TileSet* tileSet);
void GetEidtorPanels(Rectangle window, Rectangle* sidePanel, Rectangle* MainPanel, float sidePanelPosition);
void DrawTileSelector(Rectangle* sidePanel, TileSet* tileSet);

#endif