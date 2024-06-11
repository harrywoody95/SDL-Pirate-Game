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
			Sprite s = *Sprites[x];
			s.Update();
		}
	}
	void Draw()
	{
		for (int x = 0; x < Sprites.size(); x++)
		{
			Sprite s = *Sprites[x];
			s.Draw();
		}
	}
};
