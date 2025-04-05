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

void SetPlayerAnimation(Game* game, Entity* Character)
{
	for (int x = 0; x < game->AnimationList.CharacterAnimations.size(); x++)
	{
		Player* Player = &Character->Player;

		if (game->AnimationList.CharacterAnimations[x].direction == Player->PlayerSprite->Movement.CurrentDirection && game->AnimationList.CharacterAnimations[x].state == Player->PlayerSprite->Movement.CurrentState)
		{
			if (Player->PlayerSprite->Movement.CurrentState != Attack)
			{
				game->AnimationList.CharacterAnimations[x].ResetAnimation();
				Player->PlayerAnimations.CharacterAnimation = &game->AnimationList.CharacterAnimations[x];
				Player->PlayerSprite->Texture = Player->PlayerAnimations.CharacterAnimation->Textures[0];
				return;
			}
			if (Player->CurrentEquipment == nullptr)
			{
				return;
			}
			if (Player->CurrentEquipment->Type == game->AnimationList.CharacterAnimations[x].equipmentType)
			{
				game->AnimationList.CharacterAnimations[x].ResetAnimation();
				Player->PlayerAnimations.CharacterAnimation = &game->AnimationList.CharacterAnimations[x];
				Player->PlayerSprite->Texture = Player->PlayerAnimations.CharacterAnimation->Textures[0];
				return;
			}
		}
	}
}

//change this entity parameter to entity eventually
void SetCostumeAnimation(Game* game, Entity* Character)
{
	Player* Player = &Character->Player;

	if (Player->CurrentCostume == nullptr)
	{
		Player->PlayerAnimations.CostumeAnimation = nullptr;
		Player->CostumeSprite->Texture = nullptr;
		return;
	}
	for (int x = 0; x < game->AnimationList.CostumeAnimations.size(); x++)
	{
		if (game->AnimationList.CostumeAnimations[x].direction == Player->PlayerSprite->Movement.CurrentDirection &&
			game->AnimationList.CostumeAnimations[x].state == Player->PlayerSprite->Movement.CurrentState &&
			Player->CurrentCostume->Type == game->AnimationList.CostumeAnimations[x].costumeType &&
			game->AnimationList.CostumeAnimations[x].colour == Player->CurrentCostume->CostumeColour)
		{
			if (Player->PlayerSprite->Movement.CurrentState != Attack)
			{
				game->AnimationList.CostumeAnimations[x].ResetAnimation();
				Player->PlayerAnimations.CostumeAnimation = &game->AnimationList.CostumeAnimations[x];
				Player->CostumeSprite->Texture = Player->PlayerAnimations.CostumeAnimation->Textures[0];
				return;
			}
			if (Player->CurrentEquipment == nullptr)
			{
				return;
			}
			if (Player->CurrentEquipment->Type == game->AnimationList.CostumeAnimations[x].equipmentType)
			{
				game->AnimationList.CostumeAnimations[x].ResetAnimation();
				Player->PlayerAnimations.CostumeAnimation = &game->AnimationList.CostumeAnimations[x];
				Player->CostumeSprite->Texture = Player->PlayerAnimations.CostumeAnimation->Textures[0];
				return;
			}
		}
	}
}

void SetEquipmentAnimation(Game* game, Entity* Character)
{
	Player* Player = &Character->Player;

	if (Player->CurrentEquipment == nullptr || Player->PlayerSprite->Movement.CurrentState == Attack)
	{
		Player->PlayerAnimations.EquipmentAnimation = nullptr;
		Player->EquipmentSprite->Texture = nullptr;
		return;
	}
	for (int x = 0; x < game->AnimationList.EquipmentAnimations.size(); x++)
	{
		if (game->AnimationList.EquipmentAnimations[x].direction == Player->PlayerSprite->Movement.CurrentDirection &&
			game->AnimationList.EquipmentAnimations[x].state == Player->PlayerSprite->Movement.CurrentState &&
			Player->CurrentEquipment->Type == game->AnimationList.EquipmentAnimations[x].equipmentType)
		{
			game->AnimationList.EquipmentAnimations[x].ResetAnimation();
			Player->PlayerAnimations.EquipmentAnimation = &game->AnimationList.EquipmentAnimations[x];
			Player->EquipmentSprite->Texture = Player->PlayerAnimations.EquipmentAnimation->Textures[0];
		}
	}
}

void SetEffectAnimation(Game* game, Entity* Character)
{
	Player* Player = &Character->Player;

	if (Player->CurrentEquipment == nullptr || Player->PlayerSprite->Movement.CurrentState != Attack)
	{
		if (Player->PlayerAnimations.EffectAnimation == nullptr)
		{
			return;
		}
		Player->PlayerAnimations.EffectAnimation = nullptr;
		Player->EffectSprite->Texture = nullptr;
		return;
	}
	for (int x = 0; x < game->AnimationList.EffectAnimations.size(); x++)
	{
		if (game->AnimationList.EffectAnimations[x].direction == Player->PlayerSprite->Movement.CurrentDirection &&
			game->AnimationList.EffectAnimations[x].state == Player->PlayerSprite->Movement.CurrentState &&
			Player->CurrentEquipment->Type == game->AnimationList.EffectAnimations[x].equipmentType)
		{
			game->AnimationList.EffectAnimations[x].ResetAnimation();
			Player->PlayerAnimations.EffectAnimation = &game->AnimationList.EffectAnimations[x];
			//normally set the first texture to sprite but this one only has two. i either handle it in code or add a transparent sprite to each effect animation.
		}
	}
}

void UpdateCharacterAnimation(Game* game, Entity* Character)
{
	Player* Player = &Character->Player;

	if (Player->PlayerSprite->Movement.LastDirection != Player->PlayerSprite->Movement.CurrentDirection || Player->PlayerSprite->Movement.LastState != Player->PlayerSprite->Movement.CurrentState)
	{
		SetPlayerAnimation(game, Character);
	}
	Player->PlayerAnimations.CharacterAnimation->Speed.Counter++;

	if (!(Player->PlayerAnimations.CharacterAnimation->Speed.Counter == Player->PlayerAnimations.CharacterAnimation->Speed.TargetUntilChange))
	{
		return;
	}

	Player->PlayerSprite->Texture = Player->PlayerAnimations.CharacterAnimation->Textures[Player->PlayerAnimations.CharacterAnimation->lastindex];
	Player->PlayerAnimations.CharacterAnimation->lastindex++;

	if (Player->PlayerAnimations.CharacterAnimation->lastindex >= Player->PlayerAnimations.CharacterAnimation->Textures.size())
	{
		Player->PlayerAnimations.CharacterAnimation->lastindex = 0;
	}

	Player->PlayerAnimations.CharacterAnimation->Speed.Counter = 0;

}

void UpdateEquipmentAnimation(Game* game, Entity* Character)
{
	Player* Player = &Character->Player;

	if (((Player->PlayerSprite->Movement.LastDirection != Player->PlayerSprite->Movement.CurrentDirection || 
		Player->PlayerSprite->Movement.LastState != Player->PlayerSprite->Movement.CurrentState) && 
		Player->CurrentEquipment != nullptr) 
		|| Player->CurrentEquipment != nullptr && Player->CurrentEquipment->Type != EquipmentType::None && Player->PlayerAnimations.EquipmentAnimation == nullptr)
	{
		SetEquipmentAnimation(game, Character);
	}
	if (Player->CurrentEquipment == nullptr || Player->CurrentEquipment->Type == EquipmentType::None || Player->PlayerAnimations.EquipmentAnimation == nullptr)
	{
		return;
	}
	Player->EquipmentSprite->Movement.Velocity = Player->PlayerSprite->Movement.Velocity;
	Player->EquipmentSprite->Movement.Speed = Player->PlayerSprite->Movement.Speed;
	Player->EquipmentSprite->Movement.Position = Player->PlayerSprite->Movement.Position;
	Player->PlayerAnimations.EquipmentAnimation->Speed.Counter++;

	if (!(Player->PlayerAnimations.EquipmentAnimation->Speed.Counter == Player->PlayerAnimations.EquipmentAnimation->Speed.TargetUntilChange))
	{
		return;
	}

	Player->EquipmentSprite->Texture = Player->PlayerAnimations.EquipmentAnimation->Textures[Player->PlayerAnimations.EquipmentAnimation->lastindex];

	Player->PlayerAnimations.EquipmentAnimation->lastindex++;

	if (Player->PlayerAnimations.EquipmentAnimation->lastindex >= Player->PlayerAnimations.EquipmentAnimation->Textures.size())
	{
		Player->PlayerAnimations.EquipmentAnimation->lastindex = 0;
	}

	Player->PlayerAnimations.EquipmentAnimation->Speed.Counter = 0;

}

void UpdateCostumeAnimation(Game* game, Entity* Character)
{
	Player* Player = &Character->Player;

	if (((Player->PlayerSprite->Movement.LastDirection != Player->PlayerSprite->Movement.CurrentDirection || 
		Player->PlayerSprite->Movement.LastState != Player->PlayerSprite->Movement.CurrentState) &&
		Player->CurrentCostume != nullptr) 
		|| Player->CurrentCostume != nullptr && Player->CurrentCostume->Type != CostumeType::None && Player->PlayerAnimations.CostumeAnimation == nullptr)
	{
		SetCostumeAnimation(game, Character);
	}
	if (Player->CurrentCostume == nullptr || Player->CurrentCostume->Type == CostumeType::None || Player->PlayerAnimations.CostumeAnimation == nullptr)
	{
		return;
	}
	Player->CostumeSprite->Movement.Velocity = Player->PlayerSprite->Movement.Velocity;
	Player->CostumeSprite->Movement.Speed = Player->PlayerSprite->Movement.Speed;
	Player->CostumeSprite->Movement.Position = Player->PlayerSprite->Movement.Position;
	Player->PlayerAnimations.CostumeAnimation->Speed.Counter++;

	if (!(Player->PlayerAnimations.CostumeAnimation->Speed.Counter == Player->PlayerAnimations.CostumeAnimation->Speed.TargetUntilChange))
	{
		return;
	}

	Player->CostumeSprite->Texture = Player->PlayerAnimations.CostumeAnimation->Textures[Player->PlayerAnimations.CostumeAnimation->lastindex];
	Player->PlayerAnimations.CostumeAnimation->lastindex++;

	if (Player->PlayerAnimations.CostumeAnimation->lastindex >= Player->PlayerAnimations.CostumeAnimation->Textures.size())
	{
		Player->PlayerAnimations.CostumeAnimation->lastindex = 0;
	}

	Player->PlayerAnimations.CostumeAnimation->Speed.Counter = 0;

}

void UpdateEffectAnimation(Game* game, Entity* Character)
{
	Player* Player = &Character->Player;

	if ((Player->PlayerSprite->Movement.LastDirection != Player->PlayerSprite->Movement.CurrentDirection || Player->PlayerSprite->Movement.LastState != Player->PlayerSprite->Movement.CurrentState) && Player->CurrentEquipment != nullptr)
	{
		SetEffectAnimation(game, Character);
	}
	if (Player->CurrentEquipment == nullptr || Player->CurrentEquipment->Type == EquipmentType::None || Player->PlayerSprite->Movement.CurrentState != Attack)
	{
		return;
	}

	Player->EffectSprite->Movement.Velocity = Player->PlayerSprite->Movement.Velocity;
	Player->EffectSprite->Movement.Speed = Player->PlayerSprite->Movement.Speed;
	Player->EffectSprite->Movement.Position = Player->PlayerSprite->Movement.Position;
	Player->PlayerAnimations.EffectAnimation->Speed.Counter++;

	if (!(Player->PlayerAnimations.EffectAnimation->Speed.Counter == Player->PlayerAnimations.EffectAnimation->Speed.TargetUntilChange))
	{
		return;
	}
	if (Player->PlayerAnimations.EffectAnimation->lastindex != 0)
	{

		Player->EffectSprite->Texture = Player->PlayerAnimations.EffectAnimation->Textures[Player->PlayerAnimations.EffectAnimation->lastindex - 1];
		Player->PlayerAnimations.EffectAnimation->lastindex++;

		if (Player->PlayerAnimations.EffectAnimation->lastindex >= Player->PlayerAnimations.EffectAnimation->Textures.size() + 1)
		{
			Player->PlayerAnimations.EffectAnimation->lastindex = 0;
		}

		Player->PlayerAnimations.EffectAnimation->Speed.Counter = 0;
		return;
	}
	if (Player->PlayerAnimations.EffectAnimation->lastindex == 0)
	{
		Player->EffectSprite->Texture = Player->PlayerAnimations.EffectAnimation->PlainTexture;
	}
	Player->PlayerAnimations.EffectAnimation->Speed.Counter = 0;
	Player->PlayerAnimations.EffectAnimation->lastindex++;
}
