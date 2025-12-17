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

void SetPlayerAnimation(Game* game, Character* Character)
{
	for (int x = 0; x < game->AnimationList.CharacterAnimations.size(); x++)
	{
		if (Character->Health < 1)
		{

			if (game->AnimationList.CharacterAnimations[x].direction == East && game->AnimationList.CharacterAnimations[x].state == Dead && Character->Sprites.Body->Movement.LastState != Dead)
			{
				game->AnimationList.CharacterAnimations[x].ResetAnimation();
				Character->PlayerAnimations.CharacterAnimation = game->AnimationList.CharacterAnimations[x];
				Character->Sprites.Body->Texture = Character->PlayerAnimations.CharacterAnimation.Textures[0];
				return;
			}
			else
				continue;
		}

		if (game->AnimationList.CharacterAnimations[x].direction == Character->Sprites.Body->Movement.CurrentDirection && game->AnimationList.CharacterAnimations[x].state == Character->Sprites.Body->Movement.CurrentState)
		{
			if (Character->Sprites.Body->Movement.CurrentState != Attack)
			{
				game->AnimationList.CharacterAnimations[x].ResetAnimation();
				Character->PlayerAnimations.CharacterAnimation = game->AnimationList.CharacterAnimations[x];
				Character->Sprites.Body->Texture = Character->PlayerAnimations.CharacterAnimation.Textures[0];
				return;
			}
			if (Character->CurrentEquipment == nullptr)
			{
				return;
			}
			if (Character->CurrentEquipment->Type == game->AnimationList.CharacterAnimations[x].equipmentType)
			{
				game->AnimationList.CharacterAnimations[x].ResetAnimation();
				Character->PlayerAnimations.CharacterAnimation = game->AnimationList.CharacterAnimations[x];
				Character->Sprites.Body->Texture = Character->PlayerAnimations.CharacterAnimation.Textures[0];
				return;
			}
		}
	}
}

//change this entity parameter to entity eventually
void SetCostumeAnimation(Game* game, Character* Character)
{
	if (Character->CurrentCostume == nullptr)
	{
		Character->PlayerAnimations.CostumeAnimation.reset();
		Character->Sprites.Costume->Texture = nullptr;
		return;
	}
	for (int x = 0; x < game->AnimationList.CostumeAnimations.size(); x++)
	{
		if (Character->Health < 1)
		{

			if (game->AnimationList.CostumeAnimations[x].direction == East && game->AnimationList.CostumeAnimations[x].state == Dead &&
				Character->CurrentCostume->Type == game->AnimationList.CostumeAnimations[x].costumeType &&
				game->AnimationList.CostumeAnimations[x].colour == Character->CurrentCostume->Colour &&
				Character->Sprites.Body->Movement.LastState != Dead)
			{
				game->AnimationList.CostumeAnimations[x].ResetAnimation();
				Character->PlayerAnimations.CostumeAnimation = {};
				Character->PlayerAnimations.CostumeAnimation = game->AnimationList.CostumeAnimations[x];
				Character->Sprites.Costume->Texture = Character->PlayerAnimations.CostumeAnimation.value().Textures[0];
				return;
			}
		}
		if (game->AnimationList.CostumeAnimations[x].direction == Character->Sprites.Body->Movement.CurrentDirection &&
			game->AnimationList.CostumeAnimations[x].state == Character->Sprites.Body->Movement.CurrentState &&
			Character->CurrentCostume->Type == game->AnimationList.CostumeAnimations[x].costumeType &&
			game->AnimationList.CostumeAnimations[x].colour == Character->CurrentCostume->Colour)
		{
			if (Character->Sprites.Body->Movement.CurrentState != Attack)
			{
				game->AnimationList.CostumeAnimations[x].ResetAnimation();
				Character->PlayerAnimations.CostumeAnimation = {};
				Character->PlayerAnimations.CostumeAnimation = game->AnimationList.CostumeAnimations[x];
				Character->Sprites.Costume->Texture = Character->PlayerAnimations.CostumeAnimation.value().Textures[0];
				return;
			}
			if (Character->CurrentEquipment == nullptr)
			{
				return;
			}
			if (Character->CurrentEquipment->Type == game->AnimationList.CostumeAnimations[x].equipmentType)
			{
				game->AnimationList.CostumeAnimations[x].ResetAnimation();
				Character->PlayerAnimations.CostumeAnimation = {};
				Character->PlayerAnimations.CostumeAnimation = game->AnimationList.CostumeAnimations[x];
				Character->Sprites.Costume->Texture = Character->PlayerAnimations.CostumeAnimation.value().Textures[0];
				return;
			}
		}
	}
}

void SetEquipmentAnimation(Game* game, Character* Character)
{
	if (Character->CurrentEquipment == nullptr || Character->Sprites.Body->Movement.CurrentState == Attack || Character->Health < 1)
	{
		Character->PlayerAnimations.EquipmentAnimation.reset();
		Character->Sprites.Equipment->Texture = nullptr;
		return;
	}
	for (int x = 0; x < game->AnimationList.EquipmentAnimations.size(); x++)
	{
		if (game->AnimationList.EquipmentAnimations[x].direction == Character->Sprites.Body->Movement.CurrentDirection &&
			game->AnimationList.EquipmentAnimations[x].state == Character->Sprites.Body->Movement.CurrentState &&
			Character->CurrentEquipment->Type == game->AnimationList.EquipmentAnimations[x].equipmentType)
		{
			game->AnimationList.EquipmentAnimations[x].ResetAnimation();
			Character->PlayerAnimations.EquipmentAnimation = {};
			Character->PlayerAnimations.EquipmentAnimation = game->AnimationList.EquipmentAnimations[x];
			Character->Sprites.Equipment->Texture = Character->PlayerAnimations.EquipmentAnimation.value().Textures[0];
		}
	}
}

void SetEffectAnimation(Game* game, Character* Character)
{
	if (Character->CurrentEquipment == nullptr || Character->Sprites.Body->Movement.CurrentState != Attack)
	{
		if (!Character->PlayerAnimations.EffectAnimation.has_value())
		{
			return;
		}
		Character->PlayerAnimations.EffectAnimation.reset();
		Character->EffectSprite->Texture = nullptr;
		return;
	}
	for (int x = 0; x < game->AnimationList.EffectAnimations.size(); x++)
	{
		if (game->AnimationList.EffectAnimations[x].direction == Character->Sprites.Body->Movement.CurrentDirection &&
			game->AnimationList.EffectAnimations[x].state == Character->Sprites.Body->Movement.CurrentState &&
			Character->CurrentEquipment->Type == game->AnimationList.EffectAnimations[x].equipmentType)
		{
			game->AnimationList.EffectAnimations[x].ResetAnimation();
			Character->PlayerAnimations.EffectAnimation = game->AnimationList.EffectAnimations[x];
			//normally set the first texture to sprite but this one only has two. i either handle it in code or add a transparent sprite to each effect animation.
		}
	}
}

void UpdateCharacterAnimation(Game* game, Character* Character)
{

	if (Character->Sprites.Body->Movement.LastDirection != Character->Sprites.Body->Movement.CurrentDirection || Character->Sprites.Body->Movement.LastState != Character->Sprites.Body->Movement.CurrentState)
	{
		SetPlayerAnimation(game, Character);
	}
	Character->PlayerAnimations.CharacterAnimation.Speed.Counter++;

	if (!(Character->PlayerAnimations.CharacterAnimation.Speed.Counter == Character->PlayerAnimations.CharacterAnimation.Speed.TargetUntilChange))
	{
		return;
	}

	Character->Sprites.Body->Texture = Character->PlayerAnimations.CharacterAnimation.Textures[Character->PlayerAnimations.CharacterAnimation.lastindex];
	Character->PlayerAnimations.CharacterAnimation.lastindex++;

	if (Character->PlayerAnimations.CharacterAnimation.lastindex >= Character->PlayerAnimations.CharacterAnimation.Textures.size())
	{
		if (Character->Sprites.Body->Movement.CurrentState == Dead)
		{
			return;
		}

		Character->PlayerAnimations.CharacterAnimation.lastindex = 0;
	}

	Character->PlayerAnimations.CharacterAnimation.Speed.Counter = 0;

}

void UpdateEquipmentAnimation(Game* game, Character* Character)
{
	if (((Character->Sprites.Body->Movement.LastDirection != Character->Sprites.Body->Movement.CurrentDirection || 
		Character->Sprites.Body->Movement.LastState != Character->Sprites.Body->Movement.CurrentState) && 
		Character->CurrentEquipment != nullptr) 
		|| Character->CurrentEquipment != nullptr && Character->CurrentEquipment->Type != EquipmentType::None && !Character->PlayerAnimations.EquipmentAnimation.has_value())
	{
		SetEquipmentAnimation(game, Character);
	}
	if (Character->CurrentEquipment == nullptr || Character->CurrentEquipment->Type == EquipmentType::None || !Character->PlayerAnimations.EquipmentAnimation.has_value())
	{
		return;
	}
	Character->Sprites.Equipment->Movement.Velocity = Character->Sprites.Body->Movement.Velocity;
	Character->Sprites.Equipment->Movement.Speed = Character->Sprites.Body->Movement.Speed;
	Character->Sprites.Equipment->Movement.Position = Character->Sprites.Body->Movement.Position;
	Character->PlayerAnimations.EquipmentAnimation.value().Speed.Counter++;

	if (!(Character->PlayerAnimations.EquipmentAnimation.value().Speed.Counter == Character->PlayerAnimations.EquipmentAnimation.value().Speed.TargetUntilChange))
	{
		return;
	}

	Character->Sprites.Equipment->Texture = Character->PlayerAnimations.EquipmentAnimation.value().Textures[Character->PlayerAnimations.EquipmentAnimation.value().lastindex];

	Character->PlayerAnimations.EquipmentAnimation.value().lastindex++;

	if (Character->PlayerAnimations.EquipmentAnimation.value().lastindex >= Character->PlayerAnimations.EquipmentAnimation.value().Textures.size())
	{
		Character->PlayerAnimations.EquipmentAnimation.value().lastindex = 0;
	}

	Character->PlayerAnimations.EquipmentAnimation.value().Speed.Counter = 0;

}

void UpdateCostumeAnimation(Game* game, Character* Character)
{
	if (((Character->Sprites.Body->Movement.LastDirection != Character->Sprites.Body->Movement.CurrentDirection || 
		Character->Sprites.Body->Movement.LastState != Character->Sprites.Body->Movement.CurrentState) &&
		Character->CurrentCostume != nullptr) 
		|| Character->CurrentCostume != nullptr && Character->CurrentCostume->Type != CostumeType::None && !Character->PlayerAnimations.CostumeAnimation.has_value())
	{
		SetCostumeAnimation(game, Character);
	}
	if (Character->CurrentCostume == nullptr || Character->CurrentCostume->Type == CostumeType::None || !Character->PlayerAnimations.CostumeAnimation.has_value())
	{
		return;
	}
	Character->Sprites.Costume->Movement.Velocity = Character->Sprites.Body->Movement.Velocity;
	Character->Sprites.Costume->Movement.Speed = Character->Sprites.Body->Movement.Speed;
	Character->Sprites.Costume->Movement.Position = Character->Sprites.Body->Movement.Position;
	Character->PlayerAnimations.CostumeAnimation.value().Speed.Counter++;

	if (!(Character->PlayerAnimations.CostumeAnimation.value().Speed.Counter == Character->PlayerAnimations.CostumeAnimation.value().Speed.TargetUntilChange))
	{
		return;
	}

	Character->Sprites.Costume->Texture = Character->PlayerAnimations.CostumeAnimation.value().Textures[Character->PlayerAnimations.CostumeAnimation.value().lastindex];
	Character->PlayerAnimations.CostumeAnimation.value().lastindex++;

	if (Character->PlayerAnimations.CostumeAnimation.value().lastindex >= Character->PlayerAnimations.CostumeAnimation.value().Textures.size())
	{
		if (Character->Sprites.Body->Movement.CurrentState == Dead)
		{
			return;
		}

		Character->PlayerAnimations.CostumeAnimation.value().lastindex = 0;
	}

	Character->PlayerAnimations.CostumeAnimation.value().Speed.Counter = 0;

}

void UpdateEffectAnimation(Game* game, Character* Character)
{
	if ((Character->Sprites.Body->Movement.LastDirection != Character->Sprites.Body->Movement.CurrentDirection || Character->Sprites.Body->Movement.LastState != Character->Sprites.Body->Movement.CurrentState) && Character->CurrentEquipment != nullptr)
	{
		SetEffectAnimation(game, Character);
	}
	if (Character->CurrentEquipment == nullptr || Character->CurrentEquipment->Type == EquipmentType::None || Character->Sprites.Body->Movement.CurrentState != Attack)
	{
		return;
	}

	Character->EffectSprite->Movement.Velocity = Character->Sprites.Body->Movement.Velocity;
	Character->EffectSprite->Movement.Speed = Character->Sprites.Body->Movement.Speed;
	Character->EffectSprite->Movement.Position = Character->Sprites.Body->Movement.Position;
	Character->PlayerAnimations.EffectAnimation.value().Speed.Counter++;

	if (!(Character->PlayerAnimations.EffectAnimation.value().Speed.Counter == Character->PlayerAnimations.EffectAnimation.value().Speed.TargetUntilChange))
	{
		return;
	}
	if (Character->PlayerAnimations.EffectAnimation.value().lastindex != 0)
	{

		Character->EffectSprite->Texture = Character->PlayerAnimations.EffectAnimation.value().Textures[Character->PlayerAnimations.EffectAnimation.value().lastindex - 1];
		Character->PlayerAnimations.EffectAnimation.value().lastindex++;

		if (Character->PlayerAnimations.EffectAnimation.value().lastindex >= Character->PlayerAnimations.EffectAnimation.value().Textures.size() + 1)
		{
			Character->PlayerAnimations.EffectAnimation.value().lastindex = 0;
		}

		Character->PlayerAnimations.EffectAnimation.value().Speed.Counter = 0;
		return;
	}
	if (Character->PlayerAnimations.EffectAnimation.value().lastindex == 0)
	{
		Character->EffectSprite->Texture = Character->PlayerAnimations.EffectAnimation.value().PlainTexture;
	}
	Character->PlayerAnimations.EffectAnimation.value().Speed.Counter = 0;
	Character->PlayerAnimations.EffectAnimation.value().lastindex++;
}
