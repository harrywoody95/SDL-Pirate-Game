#include "Player.h"
#include "game.h"
#include <fstream>
#include <iostream>

void UpdatePlayerCollision(Game* game);
void HandlePlayerProjectileFiring(Game* game);
void UpdatePlayerAnimation(Game* game);

bool CanFireGun = true;
void Player::CreatePlayer(float x, float y, Game* game)
{
	PlayerSprite = new Sprite();
	PlayerSprite->CreateSprite(x, y, "Assets/Sprites/transparent.png", 16, 4, &game->SpriteList);
	CostumeSprite = new Sprite();
	CostumeSprite->CreateSprite(x, y, "Assets/Sprites/transparent.png", 16, 4, &game->SpriteList);
	EquipmentSprite = new Sprite();
	EquipmentSprite->CreateSprite(x, y, "Assets/Sprites/transparent.png", 16, 4, &game->SpriteList);
	EffectSprite = new Sprite();
	EffectSprite->CreateSprite(x, y, "Assets/Sprites/transparent.png", 16, 4, &game->SpriteList);
	PlayerSprite->Name = "PlayerSprite";
	CostumeSprite->Name = "CostumeSprite";
	EquipmentSprite->Name = "EquipmentSprite";
	EffectSprite->Name = "EffectSprite";
	SetPlayerAnimation(game);
	SetCostumeAnimation(game);
	SetEquipmentAnimation(game);
}

void HandlePlayerProjectileFiring(Game* game)
{
	if (game->Player.CurrentEquipment == nullptr || game->Player.CurrentEquipment->Type == EquipmentType::Sword)
	{
		return;
	}

	if (CanFireGun)
	{
		if (game->Player.PlayerSprite->Movement.CurrentState == Attack && game->Player.PlayerAnimations.CharacterAnimation->lastindex == 2)
		{
			Projectile Projectile(game->Player.PlayerSprite->Movement.Position.x, game->Player.PlayerSprite->Movement.Position.y, ProjectileType::Bullet, game->Player.PlayerSprite->Movement.CurrentDirection, 10, &game->SpriteList);
			game->ProjectileList.push_back(Projectile);
			CanFireGun = false;
		}
	}
	else 
	{
		if (game->Player.PlayerAnimations.CharacterAnimation->lastindex != 2)
		{
			CanFireGun = true;
		}
	}
}

void UpdatePlayerAnimation(Game* game)
{
	UpdateCharacterAnimation(game);
	UpdateCostumeAnimation(game);
	UpdateEquipmentAnimation(game);
	UpdateEffectAnimation(game);
}

void UpdatePlayerCollision(Game* game)
{
	game->Player.Collision.Left = game->Player.PlayerSprite->Movement.Position.x;
	game->Player.Collision.Top = game->Player.PlayerSprite->Movement.Position.y;
	game->Player.Collision.Right = game->Player.PlayerSprite->Movement.Position.x + (game->Player.PlayerSprite->BitSize * game->Player.PlayerSprite->Scale);
	game->Player.Collision.Bottom = game->Player.PlayerSprite->Movement.Position.y + (game->Player.PlayerSprite->BitSize * game->Player.PlayerSprite->Scale);
}

void Player::UpdatePlayer(Game* game)
{
	UpdatePlayerCollision(game);
	UpdatePlayerAnimation(game);
	HandlePlayerProjectileFiring(game);
}
