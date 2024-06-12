#pragma once
#include<vector>
#include "Sprite.h"
struct SpriteList
{
	std::vector<Sprite*> Sprites;

	void Update()
	{
		for (int x = 0; x < Sprites.size(); x++)
		{
			Sprites[x]->Update();
		}
	}
	void Draw()
	{
		for (int x = 0; x < Sprites.size(); x++)
		{
			Sprites[x]->Draw();
		}
	}
};
