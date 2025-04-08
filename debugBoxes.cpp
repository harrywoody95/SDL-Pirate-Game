#include "DebugBox.h"
#include "Game.h"

void DrawCollsionBoxes(Game* Game)
{
	Player* Player = &Game->PlayerEntity->Player;
	std::vector <Box> CollisionBoxes;

	for (int x = 0; x < Game->Map.LayerOne.size(); x++)
	{
		if (Game->Map.LayerOne[x].Solid)
		{
			CollisionBoxes.push_back(Game->Map.LayerOne[x].Collision);
		}
	}
	for (int x = 0; x < Game->Map.LayerTwo.size(); x++)
	{
		if (Game->Map.LayerTwo[x].Solid)
		{
			CollisionBoxes.push_back(Game->Map.LayerTwo[x].Collision);
		}
	}
	for (int x = 0; x < Game->Map.LayerThree.size(); x++)
	{
		if (Game->Map.LayerThree[x].Solid)
		{
			CollisionBoxes.push_back(Game->Map.LayerThree[x].Collision);
		}
	}
	std::vector <Entity*> list = GetEntitites(Game, EntityType::NPC);
	for (int x = 0; x < list.size(); x++)
	{
		CollisionBoxes.push_back(list[x]->NPC.Collision);
	}
	SDL_Texture* text = TextureManager::LoadTexture(static_cast<const char*>("Assets/Sprites/debug.png"));
	SDL_Rect Dbox, Sbox;

	for (int x = 0; x < CollisionBoxes.size(); x++)
	{
		
		Dbox.x = CollisionBoxes[x].Left;
		Dbox.y = CollisionBoxes[x].Top;
		Dbox.w = CollisionBoxes[x].Right - CollisionBoxes[x].Left;
		Dbox.h = CollisionBoxes[x].Bottom - CollisionBoxes[x].Top;

		Sbox.x = 0;
		Sbox.y = 0;
		Sbox.w = 64;
		Sbox.h = 64;

		Dbox.x = Dbox.x - Game->Camera.Position.x;
		Dbox.y = Dbox.y - Game->Camera.Position.y;

		TextureManager::Draw(text, Sbox, Dbox);
	}
	Dbox.x = Player->Collision.Left;
	Dbox.y = Player->Collision.Top;
	Dbox.w = Player->Collision.Right - Player->Collision.Left;
	Dbox.h = Player->Collision.Bottom - Player->Collision.Top;

	Sbox.x = 0;
	Sbox.y = 0;
	Sbox.w = 64;
	Sbox.h = 64;

	Dbox.x = Dbox.x - Game->Camera.Position.x;
	Dbox.y = Dbox.y - Game->Camera.Position.y;
	
	TextureManager::Draw(text, Sbox, Dbox);
	SDL_DestroyTexture(text);
}
