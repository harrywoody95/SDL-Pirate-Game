#include "Player.h"
#include "game.h"
#include <fstream>
#include <iostream>

bool CanFireGun = true;

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
	Player->PlayerSprite->Name = "PlayerSprite";
	Player->CostumeSprite->Name = "CostumeSprite";
	Player->EquipmentSprite->Name = "EquipmentSprite";
	Player->EffectSprite->Name = "EffectSprite";
	SetPlayerAnimation(game, entity);
	SetCostumeAnimation(game, entity);
	SetEquipmentAnimation(game, entity);
	return entity;
}

void HandlePlayerProjectileFiring(Game* game)
{
	Player* Player = &game->PlayerEntity->Player;

	if (Player->CurrentEquipment == nullptr || Player->CurrentEquipment->Type == EquipmentType::Sword)
	{
		return;
	}

	if (CanFireGun)
	{
		if (Player->PlayerSprite->Movement.CurrentState == Attack && Player->PlayerAnimations.CharacterAnimation->lastindex == 2)
		{
			Entity* Projectile = CreateProjectile(Player->PlayerSprite->Movement.Position.x, Player->PlayerSprite->Movement.Position.y, ProjectileType::Bullet, Player->PlayerSprite->Movement.CurrentDirection, 10, game);
			CanFireGun = false;
		}
	}
	else 
	{
		if (Player->PlayerAnimations.CharacterAnimation->lastindex != 2)
		{
			CanFireGun = true;
		}
	}
}

void UpdatePlayerAnimation(Game* game)
{
	UpdateCharacterAnimation(game, game->PlayerEntity);
	UpdateCostumeAnimation(game, game->PlayerEntity);
	UpdateEquipmentAnimation(game, game->PlayerEntity);
	UpdateEffectAnimation(game, game->PlayerEntity);
}

void UpdatePlayerCollision(Game* game)
{
	Player* Player = &game->PlayerEntity->Player;

	Player->Collision.Left = Player->PlayerSprite->Movement.Position.x;
	Player->Collision.Top = Player->PlayerSprite->Movement.Position.y;
	Player->Collision.Right = Player->PlayerSprite->Movement.Position.x + (Player->PlayerSprite->BitSize * Player->PlayerSprite->Scale);
	Player->Collision.Bottom = Player->PlayerSprite->Movement.Position.y + (Player->PlayerSprite->BitSize * Player->PlayerSprite->Scale);
}

void Player::UpdatePlayer(Game* game)
{
	UpdatePlayerCollision(game);
	UpdatePlayerAnimation(game);
	HandlePlayerProjectileFiring(game);
}
