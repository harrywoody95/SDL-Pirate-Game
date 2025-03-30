#pragma once
#include "MapTileType.h"
#include "SDL.h"
#include <iostream>
#include "Vec2.h"
#include "Collision.h"
struct Camera;
struct MapTile {
	MapTileType Type;
	SDL_Texture* Texture;
	Vec2 Position;
	Box Collision;
	bool Solid;
	int Scale;
	int Bitsize;

	void CreateMapTile(float x, float y, MapTileType Type, int BitSize, int Scale, MapTileAssets MTA, bool Solid);
	void Update(Camera* camera);
	void Draw(Camera* camera);
};
