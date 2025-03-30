#include "DebugBox.h"
#include "Game.h"
void DrawCollsionBoxes(Game* Game)
{
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
	Dbox.x = Game->Player.Collision.Left;
	Dbox.y = Game->Player.Collision.Top;
	Dbox.w = Game->Player.Collision.Right - Game->Player.Collision.Left;
	Dbox.h = Game->Player.Collision.Bottom - Game->Player.Collision.Top;

	Sbox.x = 0;
	Sbox.y = 0;
	Sbox.w = 64;
	Sbox.h = 64;

	Dbox.x = Dbox.x - Game->Camera.Position.x;
	Dbox.y = Dbox.y - Game->Camera.Position.y;

	TextureManager::Draw(text, Sbox, Dbox);

}