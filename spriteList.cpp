#include "SpriteList.h"
#include "Game.h"

void SpriteList::Draw(Game* game)
{
	SpriteList SpriteList = SortSpriteDrawingOrder(game->SpriteList);
	for (int x = 0; x < SpriteList.Sprites.size(); x++)
	{
		SpriteList.Sprites[x]->Draw(&game->Camera);
	}
}

void SpriteList::Update()
{
	for (int x = 0; x < Sprites.size(); x++)
	{
		Sprites[x]->Update();
	}
}

SpriteList SortSpriteDrawingOrder(SpriteList list)
{
	SpriteList OrderedSpriteList;
	Sprite* Lowest = nullptr;
	int size = list.Sprites.size();
	bool foundplayer = false;
	for (int y = 0; y < size; y++)
	{
		for (int x = 0; x < list. Sprites.size(); x++)
		{


			if (x == 0)
			{
				Lowest = list.Sprites[x];
			}

			else
			{
				Box a, b;
				a.Top = Lowest->Position.y;
				a.Left = Lowest->Position.x;
				a.Right = Lowest->Position.x + Lowest->BitSize * Lowest->Scale;
				a.Bottom = Lowest->Position.y + Lowest->BitSize * Lowest->Scale;

				b.Top = list.Sprites[x]->Position.y;
				b.Left = list.Sprites[x]->Position.x;
				b.Right = list.Sprites[x]->Position.x + Lowest->BitSize * Lowest->Scale;
				b.Bottom = list.Sprites[x]->Position.y + Lowest->BitSize * Lowest->Scale;

				if (b.Bottom < a.Bottom )
				{
					Lowest = list.Sprites[x];
				}
			}
		}
		OrderedSpriteList.Sprites.push_back(Lowest);
		for (int x = 0; x < list.Sprites.size(); x++)
		{
			if (Lowest == list.Sprites[x])
			{
				list.Sprites.erase(list.Sprites.begin() + x);
			}
		}
	}
	return OrderedSpriteList;
}
