#pragma once
#include "MapTileType.h"
#include "SDL.h"
#include <iostream>

struct MapTile {
	MapTileType Type;
	SDL_Rect SourceBox;
	SDL_Rect DestinationBox;
	SDL_Texture* Texture;

	void CreateMapTile(MapTileType Type, SDL_Rect SourceBox, SDL_Rect DestinationBox, MapTileAssets MTA);
	SDL_Rect Update(Camera* camera);
};
