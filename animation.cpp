#include "Animation.h"
#include "Game.h"
#include<fstream>
#include "Player.h"

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
		std::string Name = DirectionToString(e->Movement.CurrentDirection) + "-" + StateToString(e->Movement.CurrentState);
		StartSpriteAnimation(game, Character->Sprites.Body, Name, true);
		return;
	}

	if (Character->CurrentEquipment == nullptr)
	{
		return;
	}

	std::string Name = DirectionToString(e->Movement.CurrentDirection) + "-" + StateToString(e->Movement.CurrentState) + "-" + EquipmentTypeToString(Character->CurrentEquipment->Type);
	StartSpriteAnimation(game, Character->Sprites.Body, Name, true);
	return;

}

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
			std::string Name = "Player-Die-" + CostumeTypeToString(Character->CurrentCostume->Type) + "-" + ColourToString(Character->CurrentCostume->Colour);
			StartSpriteAnimation(game, Character->Sprites.Costume, Name, false);
			return;
		}
	}

	if (e->Movement.CurrentState != Attack && e->Movement.CurrentState != Dead)
	{
		std::string Name = DirectionToString(e->Movement.CurrentDirection) + "-" + StateToString(e->Movement.CurrentState) + "-" + CostumeTypeToString(Character->CurrentCostume->Type) + "-" + ColourToString(Character->CurrentCostume->Colour);
		StartSpriteAnimation(game, Character->Sprites.Costume, Name, true);
		return;
	}
	if (Character->CurrentEquipment == nullptr || e->Movement.CurrentState == Dead)
	{
		return;
	}

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
		delete(Character->Sprites.Equipment->Animation);
		Character->Sprites.Equipment->Animation = nullptr;
		Character->Sprites.Equipment->Texture = Character->TransparentTexture;
		return;
	}

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

	delete (Character->EffectSprite->Animation);
	Character->EffectSprite->Animation = nullptr;
	Character->EffectSprite->Texture = Character->TransparentTexture;

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
}
