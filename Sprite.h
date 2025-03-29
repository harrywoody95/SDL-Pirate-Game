#pragma once
#include "SDL.h"
#include "Movement.h"
#include <vector>
#include <String>

struct SpriteList;
struct Sprite
{
	std::string Name;
	Movement Movement;
	SDL_Texture* Texture = nullptr;
	int Scale;
	int BitSize;
	SDL_Rect CollisionBox = {};

	void CreateSprite(float x, float y, const char* Filename, int SpriteBitSize, int Scale, SpriteList* SpriteList);
	void DeleteSprite(SpriteList* SpriteList);

	void Update();
	void Draw();
};
