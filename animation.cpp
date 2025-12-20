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

void SetPlayerAnimation(Game* game, Entity* e)
{
	Character* Character = nullptr;
	if (e->Type == EntityType::Player)
	{
		Character = &e->Player;
	}
	else
	{
		Character = &e->NPC;
	}


		if (Character->Health < 1)
		{

			if (e->Movement.LastState != Dead)
			{
				//game->AnimationList.CharacterAnimations[x].ResetAnimation();
				//Character->PlayerAnimations.CharacterAnimation = game->AnimationList.CharacterAnimations[x];
				//Character->Sprites.Body->Texture = Character->PlayerAnimations.CharacterAnimation.Textures[0];

				StartSpriteAnimation(game, Character->Sprites.Body, "Player-Die", false);
				return;
			}
		}

		if (e->Movement.CurrentDirection == e->Movement.LastDirection && e->Movement.CurrentState == e->Movement.LastState)
		{
			return;
		}

		if (e->Movement.CurrentState != Attack)
		{
			//game->AnimationList.CharacterAnimations[x].ResetAnimation();
			//Character->PlayerAnimations.CharacterAnimation = game->AnimationList.CharacterAnimations[x];
			//Character->Sprites.Body->Texture = Character->PlayerAnimations.CharacterAnimation.Textures[0];
			std::string Name = DirectionToString(e->Movement.CurrentDirection) + "-" + StateToString(e->Movement.CurrentState);
			StartSpriteAnimation(game, Character->Sprites.Body, Name, true);
			return;
		}

		if (Character->CurrentEquipment == nullptr)
		{
			return;
		}

			//game->AnimationList.CharacterAnimations[x].ResetAnimation();
			//Character->PlayerAnimations.CharacterAnimation = game->AnimationList.CharacterAnimations[x];
			//Character->Sprites.Body->Texture = Character->PlayerAnimations.CharacterAnimation.Textures[0];
			std::string Name = DirectionToString(e->Movement.CurrentDirection) + "-" + StateToString(e->Movement.CurrentState) + "-" + EquipmentTypeToString(Character->CurrentEquipment->Type);
			StartSpriteAnimation(game, Character->Sprites.Body, Name, true);
			return;

}

//change this entity parameter to entity eventually
void SetCostumeAnimation(Game* game, Entity* e)
{
	Character* Character = nullptr;
	if (e->Type == EntityType::Player)
	{
		Character = &e->Player;
	}
	else
	{
		Character = &e->NPC;
	}


	if (Character->CurrentCostume == nullptr)
	{
		if (Character->Sprites.Costume->Animation != nullptr)
		{
			delete(Character->Sprites.Costume->Animation);
			Character->Sprites.Costume->Animation = nullptr;
		}
		return;
	}

	if (Character->Health < 1)
	{

		if (e->Movement.LastState != Dead)
		{
			//game->AnimationList.CostumeAnimations[x].ResetAnimation();
			//Character->PlayerAnimations.CostumeAnimation = {};
			//Character->PlayerAnimations.CostumeAnimation = game->AnimationList.CostumeAnimations[x];
			//Character->Sprites.Costume->Texture = Character->PlayerAnimations.CostumeAnimation.value().Textures[0];
			std::string Name = "Player-Die-" + CostumeTypeToString(Character->CurrentCostume->Type) + "-" + ColourToString(Character->CurrentCostume->Colour);
			StartSpriteAnimation(game, Character->Sprites.Costume, Name, false);
			return;
		}
	}

	if (e->Movement.CurrentState != Attack && e->Movement.CurrentState != Dead)
	{
		//game->AnimationList.CostumeAnimations[x].ResetAnimation();
		//Character->PlayerAnimations.CostumeAnimation = {};
		//Character->PlayerAnimations.CostumeAnimation = game->AnimationList.CostumeAnimations[x];
		//Character->Sprites.Costume->Texture = Character->PlayerAnimations.CostumeAnimation.value().Textures[0];
		std::string Name = DirectionToString(e->Movement.CurrentDirection) + "-" + StateToString(e->Movement.CurrentState) + "-" + CostumeTypeToString(Character->CurrentCostume->Type) + "-" + ColourToString(Character->CurrentCostume->Colour);
		StartSpriteAnimation(game, Character->Sprites.Costume, Name, true);
		return;
	}
	if (Character->CurrentEquipment == nullptr || e->Movement.CurrentState == Dead)
	{
		return;
	}

	//game->AnimationList.CostumeAnimations[x].ResetAnimation();
	//Character->PlayerAnimations.CostumeAnimation = {};
	//Character->PlayerAnimations.CostumeAnimation = game->AnimationList.CostumeAnimations[x];
	//Character->Sprites.Costume->Texture = Character->PlayerAnimations.CostumeAnimation.value().Textures[0];
	std::string Name = DirectionToString(e->Movement.CurrentDirection) + "-" + StateToString(e->Movement.CurrentState) + "-" + EquipmentTypeToString(Character->CurrentEquipment->Type) + "-" + 
		CostumeTypeToString(Character->CurrentCostume->Type) + "-" + ColourToString(Character->CurrentCostume->Colour);

	StartSpriteAnimation(game, Character->Sprites.Costume, Name, true);
	return;
}

void SetEquipmentAnimation(Game* game, Entity* e)
{
	Character* Character = nullptr;
	if (e->Type == EntityType::Player)
	{
		Character = &e->Player;
	}
	else
	{
		Character = &e->NPC;
	}


	if (Character->CurrentEquipment == nullptr || e->Movement.CurrentState == Attack || Character->Health < 1)
	{
		//Character->PlayerAnimations.EquipmentAnimation.reset();
		//Character->Sprites.Equipment->Texture = nullptr;
		delete(Character->Sprites.Equipment->Animation);
		Character->Sprites.Equipment->Animation = nullptr;
		Character->Sprites.Equipment->Texture = TextureManager::LoadTexture("Assets/Sprites/Character/transparent.png");
		return;
	}


			//game->AnimationList.EquipmentAnimations[x].ResetAnimation();
			//Character->PlayerAnimations.EquipmentAnimation = {};
			//Character->PlayerAnimations.EquipmentAnimation = game->AnimationList.EquipmentAnimations[x];
			//Character->Sprites.Equipment->Texture = Character->PlayerAnimations.EquipmentAnimation.value().Textures[0];
			std::string Name = DirectionToString(e->Movement.CurrentDirection) + "-" + StateToString(e->Movement.CurrentState) + "-" + EquipmentTypeToString(Character->CurrentEquipment->Type);
			StartSpriteAnimation(game, Character->Sprites.Equipment, Name, true);
		
	
}

void SetEffectAnimation(Game* game, Entity* e)
{

	Character* Character = nullptr;
	if (e->Type == EntityType::Player)
	{
		Character = &e->Player;
	}
	else
	{
		Character = &e->NPC;
	}


	if (Character->CurrentEquipment == nullptr || e->Movement.CurrentState != Attack)
	{
		if (Character->EffectSprite->Animation == nullptr)
		{
			return;
		}
		delete (Character->EffectSprite->Animation);
		Character->EffectSprite->Animation = nullptr;
		return;
	}


	//game->AnimationList.EffectAnimations[x].ResetAnimation();
	//Character->PlayerAnimations.EffectAnimation = game->AnimationList.EffectAnimations[x];
	//normally set the first texture to sprite but this one only has two. i either handle it in code or add a transparent sprite to each effect animation.
	std::string Name = DirectionToString(e->Movement.CurrentDirection) + "-" + StateToString(e->Movement.CurrentState) + "-" + EquipmentTypeToString(Character->CurrentEquipment->Type) + "-" + "Effect";
	StartSpriteAnimation(game, Character->EffectSprite, Name, true);
		
	
}

void UpdateCharacterAnimation(Game* game, Entity* e)
{
	Character* Character = nullptr;
	if (e->Type == EntityType::Player)
	{
		Character = &e->Player;
	}
	else 
	{
		Character = &e->NPC;
	}

	if (e->Movement.LastDirection != e->Movement.CurrentDirection || e->Movement.LastState != e->Movement.CurrentState)
	{
		SetPlayerAnimation(game, e);
	}
	/*Character->PlayerAnimations.CharacterAnimation.Speed.Counter++;

	if (!(Character->PlayerAnimations.CharacterAnimation.Speed.Counter == Character->PlayerAnimations.CharacterAnimation.Speed.TargetUntilChange))
	{
		return;
	}

	Character->Sprites.Body->Texture = Character->PlayerAnimations.CharacterAnimation.Textures[Character->PlayerAnimations.CharacterAnimation.lastindex];
	Character->PlayerAnimations.CharacterAnimation.lastindex++;

	if (Character->PlayerAnimations.CharacterAnimation.lastindex >= Character->PlayerAnimations.CharacterAnimation.Textures.size())
	{
		if (e->Movement.CurrentState == Dead)
		{
			return;
		}

		Character->PlayerAnimations.CharacterAnimation.lastindex = 0;
	}

	Character->PlayerAnimations.CharacterAnimation.Speed.Counter = 0;*/

}

void UpdateEquipmentAnimation(Game* game, Entity* e)
{
	Character* Character = nullptr;
	if (e->Type == EntityType::Player)
	{
		Character = &e->Player;
	}
	else 
	{
		Character = &e->NPC;
	}

	if (((e->Movement.LastDirection != e->Movement.CurrentDirection || 
		e->Movement.LastState != e->Movement.CurrentState) && 
		Character->CurrentEquipment != nullptr) 
		|| Character->CurrentEquipment != nullptr && Character->CurrentEquipment->Type != EquipmentType::None && Character->Sprites.Equipment->Animation == nullptr)
	{
		SetEquipmentAnimation(game, e);
	}
	//if (Character->CurrentEquipment == nullptr || Character->CurrentEquipment->Type == EquipmentType::None || !Character->PlayerAnimations.EquipmentAnimation.has_value())
	//{
	//	return;
	//}
	////e->Movement.Velocity = Character->Movement.Velocity;
	////Character->Sprites.Equipment->Movement.Speed = Character->Movement.Speed;
	////Character->Sprites.Equipment->Movement.Position = Character->Movement.Position;
	//Character->PlayerAnimations.EquipmentAnimation.value().Speed.Counter++;

	//if (!(Character->PlayerAnimations.EquipmentAnimation.value().Speed.Counter == Character->PlayerAnimations.EquipmentAnimation.value().Speed.TargetUntilChange))
	//{
	//	return;
	//}

	//Character->Sprites.Equipment->Texture = Character->PlayerAnimations.EquipmentAnimation.value().Textures[Character->PlayerAnimations.EquipmentAnimation.value().lastindex];

	//Character->PlayerAnimations.EquipmentAnimation.value().lastindex++;

	//if (Character->PlayerAnimations.EquipmentAnimation.value().lastindex >= Character->PlayerAnimations.EquipmentAnimation.value().Textures.size())
	//{
	//	Character->PlayerAnimations.EquipmentAnimation.value().lastindex = 0;
	//}

	//Character->PlayerAnimations.EquipmentAnimation.value().Speed.Counter = 0;

}

void UpdateCostumeAnimation(Game* game, Entity* e)
{
	Character* Character = nullptr;
	if (e->Type == EntityType::Player)
	{
		Character = &e->Player;
	}
	else 
	{
		Character = &e->NPC;
	}

	if (((e->Movement.LastDirection != e->Movement.CurrentDirection || 
		e->Movement.LastState != e->Movement.CurrentState) &&
		Character->CurrentCostume != nullptr) 
		|| Character->CurrentCostume != nullptr && Character->CurrentCostume->Type != CostumeType::None && Character->Sprites.Costume->Animation == nullptr)
	{
		SetCostumeAnimation(game, e);
	}
	//if (Character->CurrentCostume == nullptr || Character->CurrentCostume->Type == CostumeType::None || !Character->PlayerAnimations.CostumeAnimation.has_value())
	//{
	//	return;
	//}
	////Character->Sprites.Costume->Movement.Velocity = Character->Movement.Velocity;
	////Character->Sprites.Costume->Movement.Speed = Character->Movement.Speed;
	////Character->Sprites.Costume->Movement.Position = Character->Movement.Position;
	//Character->PlayerAnimations.CostumeAnimation.value().Speed.Counter++;

	//if (!(Character->PlayerAnimations.CostumeAnimation.value().Speed.Counter == Character->PlayerAnimations.CostumeAnimation.value().Speed.TargetUntilChange))
	//{
	//	return;
	//}

	//Character->Sprites.Costume->Texture = Character->PlayerAnimations.CostumeAnimation.value().Textures[Character->PlayerAnimations.CostumeAnimation.value().lastindex];
	//Character->PlayerAnimations.CostumeAnimation.value().lastindex++;

	//if (Character->PlayerAnimations.CostumeAnimation.value().lastindex >= Character->PlayerAnimations.CostumeAnimation.value().Textures.size())
	//{
	//	if (e->Movement.CurrentState == Dead)
	//	{
	//		return;
	//	}

	//	Character->PlayerAnimations.CostumeAnimation.value().lastindex = 0;
	//}

	//Character->PlayerAnimations.CostumeAnimation.value().Speed.Counter = 0;

}

void UpdateEffectAnimation(Game* game, Entity* e)
{
	Character* Character = nullptr;
	if (e->Type == EntityType::Player)
	{
		Character = &e->Player;
	}
	else
	{
		Character = &e->NPC;
	}

	if ((e->Movement.LastDirection != e->Movement.CurrentDirection || e->Movement.LastState != e->Movement.CurrentState) && Character->CurrentEquipment != nullptr)
	{
		SetEffectAnimation(game, e);
	}
	/*if (Character->CurrentEquipment == nullptr || Character->CurrentEquipment->Type == EquipmentType::None || e->Movement.CurrentState != Attack)
	{
		return;
	}

	if (!Character->PlayerAnimations.EffectAnimation.has_value())
	{
		return;
	}

	Character->EffectSprite->Position = e->Movement.Position;
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
	Character->PlayerAnimations.EffectAnimation.value().lastindex++;*/
}
