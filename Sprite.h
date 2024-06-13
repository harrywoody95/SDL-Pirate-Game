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
	SDL_Texture* Texture;
	SDL_Texture* Costume = nullptr;
	SDL_Rect SourceBox;
	SDL_Rect DestinationBox;

	void CreateSprite(float x, float y, const char* Filename, int SpriteBitSize, int Scale, SpriteList* SpriteList);
	void DeleteSprite(SpriteList* SpriteList);


	void Update()
	{
		Movement.Update();
		DestinationBox.x = Movement.Position.x;
		DestinationBox.y = Movement.Position.y;
	}
	void Draw();

};


