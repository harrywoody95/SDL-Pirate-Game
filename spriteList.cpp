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
	//SpriteList oldList = list;
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

				if (b.Bottom < a.Bottom )//- ((a.Bottom - a.Top) / 2))
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
	//int playerindex = -1;
	//int costumeindex = -1;
	//int equipmentindex = -1;
	//int effectindex = -1;
	//int listindex = 0;
	//for (listindex; listindex < OrderedSpriteList->Sprites.size(); listindex++)
	//{
	//	if (OrderedSpriteList->Sprites[listindex]->Name == "PlayerSprite")
	//	{
	//		playerindex = listindex;
	//	}
	//	if (OrderedSpriteList->Sprites[listindex]->Name == "CostumeSprite")
	//	{
	//		costumeindex = listindex;
	//	}
	//	if (OrderedSpriteList->Sprites[listindex]->Name == "EquipmentSprite")
	//	{
	//		equipmentindex = listindex;
	//	}
	//	if (OrderedSpriteList->Sprites[listindex]->Name == "EffectSprite")
	//	{
	//		effectindex = listindex;
	//	}
	//	if (playerindex > -1 && costumeindex > -1 && equipmentindex > -1 && effectindex > -1)
	//	{
	//		std::cout << playerindex << costumeindex << equipmentindex << effectindex << std::endl;
	//		// If PlayerSprite and CostumeSprite are not in correct order, swap them
	//		if (costumeindex < playerindex) {
	//			std::swap(OrderedSpriteList->Sprites[playerindex], OrderedSpriteList->Sprites[costumeindex]);
	//			playerindex = costumeindex;  // Update the playerindex after swap
	//		}

	//		// If EquipmentSprite is not in correct order, swap it
	//		if (equipmentindex < costumeindex) {
	//			std::swap(OrderedSpriteList->Sprites[costumeindex], OrderedSpriteList->Sprites[equipmentindex]);
	//			costumeindex = equipmentindex;  // Update the costumeindex after swap
	//		}

	//		// If EffectSprite is not in correct order, swap it
	//		if (effectindex < equipmentindex) {
	//			std::swap(OrderedSpriteList->Sprites[equipmentindex], OrderedSpriteList->Sprites[effectindex]);
	//			equipmentindex = effectindex;
	//		}
	//		std::cout << playerindex << costumeindex << equipmentindex << effectindex << std::endl;

	//		playerindex = -1;
	//		costumeindex = -1;
	//		equipmentindex = -1;
	//		effectindex = -1;
	//	}
	//}
	return OrderedSpriteList;
}
