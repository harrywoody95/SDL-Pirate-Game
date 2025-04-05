#include "Player.h"
#include "game.h"
#include <fstream>
#include <iostream>

void UpdatePlayerCollision(Game* game);
void HandlePlayerProjectileFiring(Game* game);
void UpdatePlayerAnimation(Game* game);

bool CanFireGun = true;
void Player::CreatePlayer(float x, float y, Game* game, Entity* Player)
{
	PlayerSprite = new Sprite();
	PlayerSprite->CreateSprite(x, y, "Assets/Sprites/Character/transparent.png", 16, 4, &game->SpriteList);
	CostumeSprite = new Sprite();
	CostumeSprite->CreateSprite(x, y, "Assets/Sprites/Character/transparent.png", 16, 4, &game->SpriteList);
	EquipmentSprite = new Sprite();
	EquipmentSprite->CreateSprite(x, y, "Assets/Sprites/Character/transparent.png", 16, 4, &game->SpriteList);
	EffectSprite = new Sprite();
	EffectSprite->CreateSprite(x, y, "Assets/Sprites/Character/transparent.png", 16, 4, &game->SpriteList);
	PlayerSprite->Name = "PlayerSprite";
	CostumeSprite->Name = "CostumeSprite";
	EquipmentSprite->Name = "EquipmentSprite";
	EffectSprite->Name = "EffectSprite";
	SetPlayerAnimation(game, Player);
	SetCostumeAnimation(game, Player);
	SetEquipmentAnimation(game, Player);
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
			Projectile Projectile(Player->PlayerSprite->Movement.Position.x, Player->PlayerSprite->Movement.Position.y, ProjectileType::Bullet, Player->PlayerSprite->Movement.CurrentDirection, 10, &game->SpriteList);
			game->ProjectileList.push_back(Projectile);
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
