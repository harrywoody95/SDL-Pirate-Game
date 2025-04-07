#include "Player.h"
#include "game.h"
#include <fstream>
#include <iostream>

//bool CanFireGun = true;

Entity* CreatePlayer(float x, float y, Game* game)
{
	Entity* entity = CreateEntity(x, y, game, EntityType::Player);
	Player* Player = &entity->Player;
	Player->PlayerSprite = new Sprite();
	Player->PlayerSprite->CreateSprite(x, y, "Assets/Sprites/Character/transparent.png", 16, 4, &game->SpriteList);
	Player->CostumeSprite = new Sprite();
	Player->CostumeSprite->CreateSprite(x, y, "Assets/Sprites/Character/transparent.png", 16, 4, &game->SpriteList);
	Player->EquipmentSprite = new Sprite();
	Player->EquipmentSprite->CreateSprite(x, y, "Assets/Sprites/Character/transparent.png", 16, 4, &game->SpriteList);
	Player->EffectSprite = new Sprite();
	Player->EffectSprite->CreateSprite(x, y, "Assets/Sprites/Character/transparent.png", 16, 4, &game->SpriteList);
	//Player->PlayerSprite->Name = "PlayerSprite";
	//Player->CostumeSprite->Name = "CostumeSprite";
	//Player->EquipmentSprite->Name = "EquipmentSprite";
	//Player->EffectSprite->Name = "EffectSprite";
	SetPlayerAnimation(game, Player);
	SetCostumeAnimation(game, Player);
	SetEquipmentAnimation(game, Player);
	return entity;
}

//void HandleCharacterProjectileFiring(Character* character, Game* game)
//{
//	//Player* Player = &game->PlayerEntity->Player;
//
//	if (character->CurrentEquipment == nullptr || character->CurrentEquipment->Type == EquipmentType::Sword)
//	{
//		return;
//	}
//
//	if (CanFireGun)
//	{
//		if (character->PlayerSprite->Movement.CurrentState == Attack && character->PlayerAnimations.CharacterAnimation->lastindex == 2)
//		{
//			Entity* Projectile = CreateProjectile(character->PlayerSprite->Movement.Position.x, character->PlayerSprite->Movement.Position.y, ProjectileType::Bullet, character->PlayerSprite->Movement.CurrentDirection, 10, game);
//			CanFireGun = false;
//		}
//	}
//	else 
//	{
//		if (character->PlayerAnimations.CharacterAnimation->lastindex != 2)
//		{
//			CanFireGun = true;
//		}
//	}
//}

//void UpdatePlayerAnimation(Game* game)
//{
//	UpdateCharacterAnimation(game, game->PlayerEntity);
//	UpdateCostumeAnimation(game, game->PlayerEntity);
//	UpdateEquipmentAnimation(game, game->PlayerEntity);
//	UpdateEffectAnimation(game, game->PlayerEntity);
//}

//void UpdateCharacterCollision(Character* character)
//{
//	character->Collision.Left = character->PlayerSprite->Movement.Position.x;
//	character->Collision.Top = character->PlayerSprite->Movement.Position.y;
//	character->Collision.Right = character->PlayerSprite->Movement.Position.x + (character->PlayerSprite->BitSize * character->PlayerSprite->Scale);
//	character->Collision.Bottom = character->PlayerSprite->Movement.Position.y + (character->PlayerSprite->BitSize * character->PlayerSprite->Scale);
//}

void Player::UpdatePlayer(Game* game)
{
	UpdateCharacterCollision(this);
	UpdateAllCharacterAnimation(game, this);
	HandleCharacterProjectileFiring(this, game);
}
