#include "Player.h"
#include "game.h"
#include <fstream>
#include <iostream>

bool CanFireGun = true;

void Player::HandleProjectileFiring(Game* game)
{
	if (CurrentEquipment == nullptr || CurrentEquipment->Type == EquipmentType::Sword)
	{
		return;
	}

	if (CanFireGun)
	{
		if (PlayerSprite->Movement.CurrentState == Attack && PlayerAnimations.CharacterAnimation->lastindex == 2)
		{
			Projectile Projectile(PlayerSprite->Movement.Position.x, PlayerSprite->Movement.Position.y, ProjectileType::Bullet, PlayerSprite->Movement.CurrentDirection, 10, &game->SpriteList);
			game->ProjectileList.push_back(Projectile);
			CanFireGun = false;
		}
	}
	else 
	{
		if (PlayerAnimations.CharacterAnimation->lastindex != 2)
		{
			CanFireGun = true;
		}
	}
}

void Player::UpdatePlayerAnimation(Game* game)
{
	UpdateCharacterAnimation(game);
	UpdateCostumeAnimation(game);
	UpdateEquipmentAnimation(game);
	UpdateEffectAnimation(game);
}

void Player::UpdatePlayerCollision(Game* game)
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
	HandleProjectileFiring(game);
}
