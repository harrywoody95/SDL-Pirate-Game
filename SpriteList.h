#pragma once
#include<vector>
#include "Sprite.h"
struct Game;
struct SpriteList
{
	std::vector<Sprite*> Sprites;

	void Update();
	void Draw(Game* game);
};
