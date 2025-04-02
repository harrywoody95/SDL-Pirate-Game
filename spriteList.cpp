#include "SpriteList.h"
#include "Game.h"
void SpriteList::Draw(Game* game)
{
	for (int x = 0; x < Sprites.size(); x++)
	{
		Sprites[x]->Draw(&game->Camera);
	}
}

void SpriteList::Update()
{
	for (int x = 0; x < Sprites.size(); x++)
	{
		Sprites[x]->Update();
	}
}