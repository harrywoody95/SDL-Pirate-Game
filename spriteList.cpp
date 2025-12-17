#include "SpriteList.h"
#include "Game.h"

void SpriteList::Draw(Game* game)
{
	SpriteList* SpriteList = SortSpriteDrawingOrder(game->SpriteList);
	for (int x = 0; x < SpriteList->Sprites.size(); x++)
	{
		SpriteList->Sprites[x]->Draw(&game->Camera);
	}
}

void SpriteList::Update()
{
	for (int x = 0; x < Sprites.size(); x++)
	{
		Sprites[x]->Update();
	}
}

SpriteList* SortSpriteDrawingOrder(SpriteList list)
{
	SpriteList* OrderedSpriteList = new SpriteList();
	Sprite* Lowest = new Sprite();
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
				a.Top = Lowest->Movement.Position.y;
				a.Left = Lowest->Movement.Position.x;
				a.Right = Lowest->Movement.Position.x + Lowest->BitSize * Lowest->Scale;
				a.Bottom = Lowest->Movement.Position.y + Lowest->BitSize * Lowest->Scale;

				b.Top = list.Sprites[x]->Movement.Position.y;
				b.Left = list.Sprites[x]->Movement.Position.x;
				b.Right = list.Sprites[x]->Movement.Position.x + Lowest->BitSize * Lowest->Scale;
				b.Bottom = list.Sprites[x]->Movement.Position.y + Lowest->BitSize * Lowest->Scale;

				if (b.Bottom < a.Bottom )
				{
					Lowest = list.Sprites[x];
				}
			}
		}
		OrderedSpriteList->Sprites.push_back(Lowest);
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
