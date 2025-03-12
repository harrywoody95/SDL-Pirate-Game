#pragma once
#include <Vector>
#include <SDL.h>
#include "TextureManager.h"
enum MapTileType {
	Water = 0,
};

struct MapTileTexture {
	SDL_Texture* Texture;
	MapTileType Type;
};

struct MapTileAssets {
	std::vector <MapTileTexture> MapTiles;

	void LoadMapTileAssets()
	{
		MapTileTexture MapTileTexture;

		MapTileTexture.Texture = TextureManager::LoadTexture("Assets/MapTiles/water.png");
		MapTileTexture.Type = (MapTileType)0;
		MapTiles.push_back(MapTileTexture);
	}
};
