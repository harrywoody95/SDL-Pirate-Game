#include "Animation.h"
#include "Game.h"
#include<fstream>

#include "Player.h"

Animation::Animation(std::string BasePath, std::string BaseFile, int frames, Direction Direction, State State)
{
	direction = Direction;
	state = State;

	for (int index = 1; index < frames + 1; index++)
	{
		std::string FullFilePath = BasePath + BaseFile + "-" + std::to_string(index) + ".png";
		const char* File = FullFilePath.c_str();
		SDL_Texture* Texture = TextureManager::LoadTexture(File);
		Textures.push_back(Texture);
	}
}

Animation::Animation(std::string BasePath, std::string BaseFile, int frames, Direction Direction, State State, EquipmentType EquipmentType)
{
	direction = Direction;
	state = State;
	equipmentType = EquipmentType;

	for (int index = 1; index < frames + 1; index++)
	{
		std::string FullFilePath = BasePath + BaseFile + "-" + std::to_string(index) + ".png";
		const char* File = FullFilePath.c_str();
		SDL_Texture* Texture = TextureManager::LoadTexture(File);
		Textures.push_back(Texture);
	}
}

Animation::Animation(std::string BasePath, std::string BaseFile, int frames, Direction Direction, State State, CostumeType CostumeType, Colour Colour)
{
	direction = Direction;
	state = State;
	costumeType = CostumeType;
	colour = Colour;

	for (int index = 1; index < frames + 1; index++)
	{
		std::string FullFilePath = BasePath + BaseFile + "-" + std::to_string(index) + ".png";
		const char* File = FullFilePath.c_str();
		SDL_Texture* Texture = TextureManager::LoadTexture(File);
		Textures.push_back(Texture);
	}
}

Animation::Animation(std::string BasePath, std::string BaseFile, int frames, Direction Direction, State State, EquipmentType EquipmentType, CostumeType CostumeType, Colour Colour)
{
	direction = Direction;
	state = State;
	costumeType = CostumeType;
	colour = Colour;
	equipmentType = EquipmentType;

	for (int index = 1; index < frames + 1; index++)
	{
		std::string FullFilePath = BasePath + BaseFile + "-" + std::to_string(index) + ".png";
		const char* File = FullFilePath.c_str();
		SDL_Texture* Texture = TextureManager::LoadTexture(File);
		Textures.push_back(Texture);
	}
}

EquipmentType StringToEquipmentType(std::string type)
{
	if (type == "Gun")
	{
		return EquipmentType::Gun;
	}
	if (type == "Sword")
	{
		return EquipmentType::Sword;
	}
	if (type == "Shovel")
	{
		return EquipmentType::Shovel;
	}
	else
	{
		return EquipmentType::None;
	}
}

void Animation::ResetAnimation()
{
	lastindex = 0;
	Speed.Counter = 0;
}

void SetPlayerAnimation(Game* game)
{
	for (int x = 0; x < game->AnimationList.CharacterAnimations.size(); x++)
	{
		if (game->AnimationList.CharacterAnimations[x].direction == game->Player.PlayerSprite->Movement.CurrentDirection && game->AnimationList.CharacterAnimations[x].state == game->Player.PlayerSprite->Movement.CurrentState)
		{
			if (game->Player.PlayerSprite->Movement.CurrentState != Attack)
			{
				game->AnimationList.CharacterAnimations[x].ResetAnimation();
				game->Player.PlayerAnimations.CharacterAnimation = &game->AnimationList.CharacterAnimations[x];
				game->Player.PlayerSprite->Texture = game->Player.PlayerAnimations.CharacterAnimation->Textures[0];
				return;
			}
			if (game->Player.CurrentEquipment == nullptr)
			{
				return;
			}
			if (game->Player.CurrentEquipment->Type == game->AnimationList.CharacterAnimations[x].equipmentType)
			{
				game->AnimationList.CharacterAnimations[x].ResetAnimation();
				game->Player.PlayerAnimations.CharacterAnimation = &game->AnimationList.CharacterAnimations[x];
				game->Player.PlayerSprite->Texture = game->Player.PlayerAnimations.CharacterAnimation->Textures[0];
				return;
			}
		}
	}
}

//change this entity parameter to entity eventually
void SetCostumeAnimation(Game* game)
{
	if (game->Player.CurrentCostume == nullptr)
	{
		game->Player.PlayerAnimations.CostumeAnimation = nullptr;
		game->Player.CostumeSprite->Texture = nullptr;
		return;
	}
	for (int x = 0; x < game->AnimationList.CostumeAnimations.size(); x++)
	{
		if (game->AnimationList.CostumeAnimations[x].direction == game->Player.PlayerSprite->Movement.CurrentDirection &&
			game->AnimationList.CostumeAnimations[x].state == game->Player.PlayerSprite->Movement.CurrentState &&
			game->Player.CurrentCostume->Type == game->AnimationList.CostumeAnimations[x].costumeType &&
			game->AnimationList.CostumeAnimations[x].colour == game->Player.CurrentCostume->CostumeColour)
		{
			if (game->Player.PlayerSprite->Movement.CurrentState != Attack)
			{
				game->AnimationList.CostumeAnimations[x].ResetAnimation();
				game->Player.PlayerAnimations.CostumeAnimation = &game->AnimationList.CostumeAnimations[x];
				game->Player.CostumeSprite->Texture = game->Player.PlayerAnimations.CostumeAnimation->Textures[0];
				return;
			}
			if (game->Player.CurrentEquipment == nullptr)
			{
				return;
			}
			if (game->Player.CurrentEquipment->Type == game->AnimationList.CostumeAnimations[x].equipmentType)
			{
				game->AnimationList.CostumeAnimations[x].ResetAnimation();
				game->Player.PlayerAnimations.CostumeAnimation = &game->AnimationList.CostumeAnimations[x];
				game->Player.CostumeSprite->Texture = game->Player.PlayerAnimations.CostumeAnimation->Textures[0];
				return;
			}
		}
	}
}

void SetEquipmentAnimation(Game* game)
{
	if (game->Player.CurrentEquipment == nullptr || game->Player.PlayerSprite->Movement.CurrentState == Attack)
	{
		game->Player.PlayerAnimations.EquipmentAnimation = nullptr;
		game->Player.EquipmentSprite->Texture = nullptr;
		return;
	}
	for (int x = 0; x < game->AnimationList.EquipmentAnimations.size(); x++)
	{
		if (game->AnimationList.EquipmentAnimations[x].direction == game->Player.PlayerSprite->Movement.CurrentDirection &&
			game->AnimationList.EquipmentAnimations[x].state == game->Player.PlayerSprite->Movement.CurrentState &&
			game->Player.CurrentEquipment->Type == game->AnimationList.EquipmentAnimations[x].equipmentType)
		{
			game->AnimationList.EquipmentAnimations[x].ResetAnimation();
			game->Player.PlayerAnimations.EquipmentAnimation = &game->AnimationList.EquipmentAnimations[x];
			game->Player.EquipmentSprite->Texture = game->Player.PlayerAnimations.EquipmentAnimation->Textures[0];
		}
	}
}

void SetEffectAnimation(Game* game)
{
	if (game->Player.CurrentEquipment == nullptr || game->Player.PlayerSprite->Movement.CurrentState != Attack)
	{
		if (game->Player.PlayerAnimations.EffectAnimation == nullptr)
		{
			return;
		}
		game->Player.PlayerAnimations.EffectAnimation = nullptr;
		game->Player.EffectSprite->Texture = nullptr;
		return;
	}
	for (int x = 0; x < game->AnimationList.EffectAnimations.size(); x++)
	{
		if (game->AnimationList.EffectAnimations[x].direction == game->Player.PlayerSprite->Movement.CurrentDirection &&
			game->AnimationList.EffectAnimations[x].state == game->Player.PlayerSprite->Movement.CurrentState &&
			game->Player.CurrentEquipment->Type == game->AnimationList.EffectAnimations[x].equipmentType)
		{
			game->AnimationList.EffectAnimations[x].ResetAnimation();
			game->Player.PlayerAnimations.EffectAnimation = &game->AnimationList.EffectAnimations[x];
			//normally set the first texture to sprite but this one only has two. i either handle it in code or add a transparent sprite to each effect animation.
		}
	}
}

void UpdateCharacterAnimation(Game* game)
{
	if (game->Player.PlayerSprite->Movement.LastDirection != game->Player.PlayerSprite->Movement.CurrentDirection || game->Player.PlayerSprite->Movement.LastState != game->Player.PlayerSprite->Movement.CurrentState)
	{
		SetPlayerAnimation(game);
	}
	game->Player.PlayerAnimations.CharacterAnimation->Speed.Counter++;

	if (!(game->Player.PlayerAnimations.CharacterAnimation->Speed.Counter == game->Player.PlayerAnimations.CharacterAnimation->Speed.TargetUntilChange))
	{
		return;
	}

	game->Player.PlayerSprite->Texture = game->Player.PlayerAnimations.CharacterAnimation->Textures[game->Player.PlayerAnimations.CharacterAnimation->lastindex];
	game->Player.PlayerAnimations.CharacterAnimation->lastindex++;

	if (game->Player.PlayerAnimations.CharacterAnimation->lastindex >= game->Player.PlayerAnimations.CharacterAnimation->Textures.size())
	{
		game->Player.PlayerAnimations.CharacterAnimation->lastindex = 0;
	}

	game->Player.PlayerAnimations.CharacterAnimation->Speed.Counter = 0;

}

void UpdateEquipmentAnimation(Game* game)
{
	if ((game->Player.PlayerSprite->Movement.LastDirection != game->Player.PlayerSprite->Movement.CurrentDirection || game->Player.PlayerSprite->Movement.LastState != game->Player.PlayerSprite->Movement.CurrentState) && game->Player.CurrentEquipment != nullptr)
	{
		SetEquipmentAnimation(game);
	}
	if (game->Player.CurrentEquipment == nullptr || game->Player.CurrentEquipment->Type == EquipmentType::None || game->Player.PlayerAnimations.EquipmentAnimation == nullptr)
	{
		return;
	}
	game->Player.EquipmentSprite->Movement.Velocity = game->Player.PlayerSprite->Movement.Velocity;
	game->Player.EquipmentSprite->Movement.Speed = game->Player.PlayerSprite->Movement.Speed;
	game->Player.EquipmentSprite->Movement.Position = game->Player.PlayerSprite->Movement.Position;
	game->Player.PlayerAnimations.EquipmentAnimation->Speed.Counter++;

	if (!(game->Player.PlayerAnimations.EquipmentAnimation->Speed.Counter == game->Player.PlayerAnimations.EquipmentAnimation->Speed.TargetUntilChange))
	{
		return;
	}

	game->Player.EquipmentSprite->Texture = game->Player.PlayerAnimations.EquipmentAnimation->Textures[game->Player.PlayerAnimations.EquipmentAnimation->lastindex];

	game->Player.PlayerAnimations.EquipmentAnimation->lastindex++;

	if (game->Player.PlayerAnimations.EquipmentAnimation->lastindex >= game->Player.PlayerAnimations.EquipmentAnimation->Textures.size())
	{
		game->Player.PlayerAnimations.EquipmentAnimation->lastindex = 0;
	}

	game->Player.PlayerAnimations.EquipmentAnimation->Speed.Counter = 0;

}

void UpdateCostumeAnimation(Game* game)
{
	if ((game->Player.PlayerSprite->Movement.LastDirection != game->Player.PlayerSprite->Movement.CurrentDirection || game->Player.PlayerSprite->Movement.LastState != game->Player.PlayerSprite->Movement.CurrentState) && game->Player.CurrentCostume != nullptr)
	{
		SetCostumeAnimation(game);
	}
	if (game->Player.CurrentCostume == nullptr || game->Player.CurrentCostume->Type == CostumeType::None || game->Player.PlayerAnimations.CostumeAnimation == nullptr)
	{
		return;
	}
	game->Player.CostumeSprite->Movement.Velocity = game->Player.PlayerSprite->Movement.Velocity;
	game->Player.CostumeSprite->Movement.Speed = game->Player.PlayerSprite->Movement.Speed;
	game->Player.CostumeSprite->Movement.Position = game->Player.PlayerSprite->Movement.Position;
	game->Player.PlayerAnimations.CostumeAnimation->Speed.Counter++;

	if (!(game->Player.PlayerAnimations.CostumeAnimation->Speed.Counter == game->Player.PlayerAnimations.CostumeAnimation->Speed.TargetUntilChange))
	{
		return;
	}

	game->Player.CostumeSprite->Texture = game->Player.PlayerAnimations.CostumeAnimation->Textures[game->Player.PlayerAnimations.CostumeAnimation->lastindex];
	game->Player.PlayerAnimations.CostumeAnimation->lastindex++;

	if (game->Player.PlayerAnimations.CostumeAnimation->lastindex >= game->Player.PlayerAnimations.CostumeAnimation->Textures.size())
	{
		game->Player.PlayerAnimations.CostumeAnimation->lastindex = 0;
	}

	game->Player.PlayerAnimations.CostumeAnimation->Speed.Counter = 0;

}

void UpdateEffectAnimation(Game* game)
{
	if ((game->Player.PlayerSprite->Movement.LastDirection != game->Player.PlayerSprite->Movement.CurrentDirection || game->Player.PlayerSprite->Movement.LastState != game->Player.PlayerSprite->Movement.CurrentState) && game->Player.CurrentEquipment != nullptr)
	{
		SetEffectAnimation(game);
	}
	if (game->Player.CurrentEquipment == nullptr || game->Player.CurrentEquipment->Type == EquipmentType::None || game->Player.PlayerSprite->Movement.CurrentState != Attack)
	{
		return;
	}

	game->Player.EffectSprite->Movement.Velocity = game->Player.PlayerSprite->Movement.Velocity;
	game->Player.EffectSprite->Movement.Speed = game->Player.PlayerSprite->Movement.Speed;
	game->Player.EffectSprite->Movement.Position = game->Player.PlayerSprite->Movement.Position;
	game->Player.PlayerAnimations.EffectAnimation->Speed.Counter++;

	if (!(game->Player.PlayerAnimations.EffectAnimation->Speed.Counter == game->Player.PlayerAnimations.EffectAnimation->Speed.TargetUntilChange))
	{
		return;
	}
	if (game->Player.PlayerAnimations.EffectAnimation->lastindex != 0)
	{

		game->Player.EffectSprite->Texture = game->Player.PlayerAnimations.EffectAnimation->Textures[game->Player.PlayerAnimations.EffectAnimation->lastindex - 1];
		game->Player.PlayerAnimations.EffectAnimation->lastindex++;

		if (game->Player.PlayerAnimations.EffectAnimation->lastindex >= game->Player.PlayerAnimations.EffectAnimation->Textures.size() + 1)
		{
			game->Player.PlayerAnimations.EffectAnimation->lastindex = 0;
		}

		game->Player.PlayerAnimations.EffectAnimation->Speed.Counter = 0;
		return;
	}
	if (game->Player.PlayerAnimations.EffectAnimation->lastindex == 0)
	{
		game->Player.EffectSprite->Texture = game->Player.PlayerAnimations.EffectAnimation->PlainTexture;
	}
	game->Player.PlayerAnimations.EffectAnimation->Speed.Counter = 0;
	game->Player.PlayerAnimations.EffectAnimation->lastindex++;
}
