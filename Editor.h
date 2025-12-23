#pragma once
#include "SDL.h"
#include "Map.h"
struct Game;
struct MapEditor {

    //Map* map;
    //MapTileAssets* assets; 
    //MapTileType currentTileType = MapTileType::Water;
    //int tileSize = 32;
    //int columns = 16;

	void RenderEditor(Game* game);
};