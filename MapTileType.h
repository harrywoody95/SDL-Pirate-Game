#pragma once
#include <Vector>
#include <SDL.h>

enum MapTileType {
	Water = 0,
};

struct MapTileTexture {
	SDL_Texture* Texture;
	MapTileType Type;
};

struct MapTileAssets {
	std::vector <MapTileTexture> MapTiles;

	void LoadMapTileAssets();
};
