#include "Sprite.h"
#include "SpriteList.h"
#include "TextureManager.h"
#include "Game.h"


void Sprite::CreateSprite(float x, float y, const char* Filename, int SpriteBitSize, int Scale, SpriteList* SpriteList)
{
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
			SDL_DestroyTexture(this->Texture);
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

	if (Animation == nullptr)
	{
		return;
	}
	Animation->CurrentTick++;

	if (Animation->Animation->TickSpeed <= Animation->CurrentTick)
	{

		Animation->CurrentTick = 0;

		if (Animation->Animation->Textures.size() == Animation->CurrentFrameIndex + 1)
		{
			if (Animation->Loop)
			{
				Animation->CurrentFrameIndex = 0;
				Texture = Animation->Animation->Textures[0];
				return;
			}
			else
			{
				delete (Animation);
				Animation = nullptr;
				return;
			}
		}
		else
		{
			Animation->CurrentFrameIndex++;
			Texture = Animation->Animation->Textures[Animation->CurrentFrameIndex];
		}
	}
	
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
		e->Player.EffectSprite->Position = e->Movement.Position;
		break;
	}
	case EntityType::NPC:
	{
		e->NPC.Sprites.Body->Position = e->Movement.Position;
		e->NPC.Sprites.Costume->Position = e->Movement.Position;
		e->NPC.Sprites.Equipment->Position = e->Movement.Position;
		e->NPC.EffectSprite->Position = e->Movement.Position;
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

SpriteAnimation* CreateSpriteAnimation(std::string Name, std::vector <SDL_Texture*> Textures, int TickSpeed)
{
	SpriteAnimation* a = new SpriteAnimation();
	a->Name = Name;
	a->Textures = Textures;
	a->TickSpeed = TickSpeed;
	return a;
}

void StartSpriteAnimation(Game* game, Sprite* Sprite, std::string Name, bool Loop)
{
	SpriteAnimationState* AnimationState = new SpriteAnimationState();
	SpriteAnimation* Animation = nullptr;

	if (Sprite->Animation != nullptr)
	{
		delete (Sprite->Animation);
		Sprite->Animation = nullptr;
	}
	for (SpriteAnimation* a : game->AnimationList)
	{
		if (a->Name == Name)
		{
			Animation = a;
			break;
		}
	}
	if(Animation == nullptr)
	{
		std::cout << "****ERROR**** Animation name : " + Name + "was not found" << std::endl;
		return;
	}

	AnimationState->CurrentTick = 0;
	AnimationState->Loop = Loop;
	AnimationState->Animation = Animation;
	AnimationState->CurrentFrameIndex = 0;

	Sprite->Animation = AnimationState;
	Sprite->Texture = Sprite->Animation->Animation->Textures[0];
}