#pragma once
#include "MapTileType.h"
#include "SDL.h"
#include <iostream>

struct MapTile {
	MapTileType Type;
	SDL_Texture* Texture;
	Vec2 Position;
	int Scale;
	int Bitsize;

	void CreateMapTile(float x, float y, MapTileType Type, int BitSize, int Scale, MapTileAssets MTA);
	void Update(Camera* camera);
	void Draw(Camera* camera);
};
