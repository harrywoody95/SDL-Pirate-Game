#pragma once
#include "SDL.h"
#include "Vec2.h"
#include <vector>
struct SpriteList;
struct Sprite
{
	Vec2 Position;
	SDL_Texture* Texture;
	SDL_Rect SourceBox;
	SDL_Rect DestinationBox;

	void CreateSprite(float x, float y, const char* Filename, int SpriteBitSize, int Scale, SpriteList* SpriteList);
	void DeleteSprite(SpriteList* SpriteList);


	void Update()
	{
		DestinationBox.x = Position.x;
		DestinationBox.y = Position.y;
	}
	void Draw();

};


