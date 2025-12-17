#include "Sprite.h"
#include "SpriteList.h"
#include "TextureManager.h"
#include "Game.h"

void Sprite::CreateSprite(float x, float y, const char* Filename, int SpriteBitSize, int Scale, SpriteList* SpriteList)
{
	//Movement.init(x, y);
	BitSize = SpriteBitSize;
	this->Scale = Scale;

	Texture = TextureManager::LoadTexture(Filename);

	SpriteList->Sprites.push_back(this);

}

void Sprite::DeleteSprite(SpriteList* SpriteList)
{
	for (int x = 0; x < SpriteList->Sprites.size(); x++)
	{
		if (this == SpriteList->Sprites[x])
		{
			SpriteList->Sprites.erase(SpriteList->Sprites.begin() + x);
			delete this;
			return;
		}
	}
}

void Sprite::Draw(Camera* Camera)
{
	SDL_Rect DestinationBox, SourceBox;
	SourceBox.x = 0;
	SourceBox.y = 0;
	SourceBox.w = BitSize;
	SourceBox.h = BitSize;

	DestinationBox.w = BitSize * Scale;
	DestinationBox.h = BitSize * Scale;
	DestinationBox.x = static_cast<int>(Position.x - Camera->Position.x);
	DestinationBox.y = static_cast<int>(Position.y - Camera->Position.y);
	// some texture mods
	//SDL_SetTextureColorMod(Texture, 100, 100, 100);
	//SDL_SetTextureAlphaMod(Texture, 50);
	TextureManager::Draw(Texture, SourceBox, DestinationBox);
}

void Sprite::Update()
{
}

void UpdateSpritePosition(Entity* e)
{
	switch (e->Type)
	{
	case EntityType::None:
	{
		break;
	}
	case EntityType::Player:
	{
		e->Player.Sprites.Body->Position = e->Movement.Position;
		e->Player.Sprites.Costume->Position = e->Movement.Position;
		e->Player.Sprites.Equipment->Position = e->Movement.Position;
		break;
	}
	case EntityType::NPC:
	{
		e->NPC.Sprites.Body->Position = e->Movement.Position;
		e->NPC.Sprites.Costume->Position = e->Movement.Position;
		e->NPC.Sprites.Equipment->Position = e->Movement.Position;
		break;
	}
	case EntityType::Projectile:
	{
		e->Projectile.ProjectileSprite->Position = e->Movement.Position;
		break;
	}
	case EntityType::Item:
	{

	}
	}
}
