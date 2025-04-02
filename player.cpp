#include "Player.h"
#include "game.h"
#include <fstream>
#include <iostream>

void Player::SetPlayerAnimation(Game* game)
{
 	for (int x = 0; x < game->AnimationList.CharacterAnimations.size(); x++)
	{
 		if (game->AnimationList.CharacterAnimations[x].direction == PlayerSprite->Movement.CurrentDirection && game->AnimationList.CharacterAnimations[x].state == PlayerSprite->Movement.CurrentState)
		{
			if (PlayerSprite->Movement.CurrentState != Attack)
			{
				game->AnimationList.CharacterAnimations[x].ResetAnimation();
				PlayerAnimations.CharacterAnimation = &game->AnimationList.CharacterAnimations[x];
				PlayerSprite->Texture = PlayerAnimations.CharacterAnimation->Textures[0];
				return;
			}
			if (CurrentEquipment == nullptr)
			{
				return;
			}
			if (CurrentEquipment->Type == game->AnimationList.CharacterAnimations[x].equipmentType)
			{
				game->AnimationList.CharacterAnimations[x].ResetAnimation();
				PlayerAnimations.CharacterAnimation = &game->AnimationList.CharacterAnimations[x];
				PlayerSprite->Texture = PlayerAnimations.CharacterAnimation->Textures[0];
				return;
			}
		}
	}
}

void Player::SetPlayerCostumeAnimation(Game* game)
{
	if (CurrentCostume == nullptr)
	{
		PlayerAnimations.CostumeAnimation = nullptr;
		game->Player.CostumeSprite->Texture = nullptr;
		return;
	}
	for (int x = 0; x < game->AnimationList.CostumeAnimations.size(); x++)
	{
		if (game->AnimationList.CostumeAnimations[x].direction == PlayerSprite->Movement.CurrentDirection && 
			game->AnimationList.CostumeAnimations[x].state == PlayerSprite->Movement.CurrentState && 
			CurrentCostume->Type == game->AnimationList.CostumeAnimations[x].costumeType && 
			game->AnimationList.CostumeAnimations[x].colour == CurrentCostume->CostumeColour)
		{
			if (PlayerSprite->Movement.CurrentState != Attack)
			{
				game->AnimationList.CostumeAnimations[x].ResetAnimation();
				PlayerAnimations.CostumeAnimation = &game->AnimationList.CostumeAnimations[x];
				CostumeSprite->Texture = PlayerAnimations.CostumeAnimation->Textures[0];
				return;
			}
			if (CurrentEquipment == nullptr)
			{
				return;
			}
			if (CurrentEquipment->Type == game->AnimationList.CostumeAnimations[x].equipmentType)
			{
				game->AnimationList.CostumeAnimations[x].ResetAnimation();
				PlayerAnimations.CostumeAnimation = &game->AnimationList.CostumeAnimations[x];
				CostumeSprite->Texture = PlayerAnimations.CostumeAnimation->Textures[0];
				return;
			}
		}
	}
}

void Player::SetPlayerEquipmentAnimation(Game* game)
{
	if (CurrentEquipment == nullptr || game->Player.PlayerSprite->Movement.CurrentState == Attack)
	{
		PlayerAnimations.EquipmentAnimation = nullptr;
		game->Player.EquipmentSprite->Texture = nullptr;
		return;
	}
	for (int x = 0; x < game->AnimationList.EquipmentAnimations.size(); x++)
	{
		if (game->AnimationList.EquipmentAnimations[x].direction == PlayerSprite->Movement.CurrentDirection &&
			game->AnimationList.EquipmentAnimations[x].state == PlayerSprite->Movement.CurrentState &&
			CurrentEquipment->Type == game->AnimationList.EquipmentAnimations[x].equipmentType)
		{
			game->AnimationList.EquipmentAnimations[x].ResetAnimation();
			PlayerAnimations.EquipmentAnimation = &game->AnimationList.EquipmentAnimations[x];
			EquipmentSprite->Texture = PlayerAnimations.EquipmentAnimation->Textures[0];
		}
	}
}

void Player::SetPlayerEffectAnimation(Game* game)
{
	if (CurrentEquipment == nullptr || PlayerSprite->Movement.CurrentState != Attack)
	{
		if (PlayerAnimations.EffectAnimation == nullptr)
		{
			return;
		}
		PlayerAnimations.EffectAnimation = nullptr;
		game->Player.EffectSprite->Texture = nullptr;
		return;
	}
	for (int x = 0; x < game->AnimationList.EffectAnimations.size(); x++)
	{
		if (game->AnimationList.EffectAnimations[x].direction == PlayerSprite->Movement.CurrentDirection &&
			game->AnimationList.EffectAnimations[x].state == PlayerSprite->Movement.CurrentState &&
			CurrentEquipment->Type == game->AnimationList.EffectAnimations[x].equipmentType)
		{
			game->AnimationList.EffectAnimations[x].ResetAnimation();
			PlayerAnimations.EffectAnimation = &game->AnimationList.EffectAnimations[x];
			//normally set the first texture to sprite but this one only has two. i either handle it in code or add a transparent sprite to each effect animation.
		}
	}
}

void Player::UpdatePlayerCharacterAnimation(Game* game)
{
	if(PlayerSprite->Movement.LastDirection != PlayerSprite->Movement.CurrentDirection || PlayerSprite->Movement.LastState != PlayerSprite->Movement.CurrentState)
	{
		SetPlayerAnimation(game);
	}
	PlayerAnimations.CharacterAnimation->Speed.Counter++;

	if (!(PlayerAnimations.CharacterAnimation->Speed.Counter == PlayerAnimations.CharacterAnimation->Speed.TargetUntilChange))
	{
		return;
	}

	PlayerSprite->Texture = PlayerAnimations.CharacterAnimation->Textures[PlayerAnimations.CharacterAnimation->lastindex];
	PlayerAnimations.CharacterAnimation->lastindex++;

	if (PlayerAnimations.CharacterAnimation->lastindex  >= PlayerAnimations.CharacterAnimation->Textures.size())
	{
		PlayerAnimations.CharacterAnimation->lastindex = 0;
	}

	PlayerAnimations.CharacterAnimation->Speed.Counter = 0;
	
}

void Player::UpdatePlayerEquipmentAnimation(Game* game)
{
	if ((PlayerSprite->Movement.LastDirection != PlayerSprite->Movement.CurrentDirection || PlayerSprite->Movement.LastState != PlayerSprite->Movement.CurrentState) && CurrentEquipment != nullptr)
	{
		SetPlayerEquipmentAnimation(game);
	}
	if (CurrentEquipment == nullptr || CurrentEquipment->Type == EquipmentType::None || PlayerAnimations.EquipmentAnimation == nullptr)
	{
		return;
	}
	EquipmentSprite->Movement.Velocity = PlayerSprite->Movement.Velocity;
	EquipmentSprite->Movement.Speed = PlayerSprite->Movement.Speed;
	EquipmentSprite->Movement.Position = PlayerSprite->Movement.Position;
	PlayerAnimations.EquipmentAnimation->Speed.Counter++;

	if (!(PlayerAnimations.EquipmentAnimation->Speed.Counter == PlayerAnimations.EquipmentAnimation->Speed.TargetUntilChange))
	{
		return;
	}

	EquipmentSprite->Texture = PlayerAnimations.EquipmentAnimation->Textures[PlayerAnimations.EquipmentAnimation->lastindex];

	PlayerAnimations.EquipmentAnimation->lastindex++;

	if (PlayerAnimations.EquipmentAnimation->lastindex >= PlayerAnimations.EquipmentAnimation->Textures.size())
	{
		PlayerAnimations.EquipmentAnimation->lastindex = 0;
	}

	PlayerAnimations.EquipmentAnimation->Speed.Counter = 0;

}

void Player::UpdatePlayerCostumeAnimation(Game* game)
{
	if ((PlayerSprite->Movement.LastDirection != PlayerSprite->Movement.CurrentDirection || PlayerSprite->Movement.LastState != PlayerSprite->Movement.CurrentState) && CurrentCostume != nullptr)
	{
		SetPlayerCostumeAnimation(game);
	}
	if (CurrentCostume == nullptr || CurrentCostume->Type == CostumeType::None || PlayerAnimations.CostumeAnimation == nullptr)
	{
		return;
	}
	CostumeSprite->Movement.Velocity = PlayerSprite->Movement.Velocity;
	CostumeSprite->Movement.Speed = PlayerSprite->Movement.Speed;
	CostumeSprite->Movement.Position = PlayerSprite->Movement.Position;
	PlayerAnimations.CostumeAnimation->Speed.Counter++;

	if (!(PlayerAnimations.CostumeAnimation->Speed.Counter == PlayerAnimations.CostumeAnimation->Speed.TargetUntilChange))
	{
		return;
	}

	CostumeSprite->Texture = PlayerAnimations.CostumeAnimation->Textures[PlayerAnimations.CostumeAnimation->lastindex];
	PlayerAnimations.CostumeAnimation->lastindex++;

	if (PlayerAnimations.CostumeAnimation->lastindex >= PlayerAnimations.CostumeAnimation->Textures.size())
	{
		PlayerAnimations.CostumeAnimation->lastindex = 0;
	}

	PlayerAnimations.CostumeAnimation->Speed.Counter = 0;
	
}

void Player::UpdatePlayerEffectAnimation(Game* game)
{
	if ((PlayerSprite->Movement.LastDirection != PlayerSprite->Movement.CurrentDirection || PlayerSprite->Movement.LastState != PlayerSprite->Movement.CurrentState) && CurrentEquipment != nullptr)
	{
		SetPlayerEffectAnimation(game);
	}
	if (CurrentEquipment == nullptr || CurrentEquipment->Type == EquipmentType::None || PlayerSprite->Movement.CurrentState != Attack)
	{
		return;
	}

	EffectSprite->Movement.Velocity = PlayerSprite->Movement.Velocity;
	EffectSprite->Movement.Speed = PlayerSprite->Movement.Speed;
	EffectSprite->Movement.Position = PlayerSprite->Movement.Position;
	PlayerAnimations.EffectAnimation->Speed.Counter++;

	if (!(PlayerAnimations.EffectAnimation->Speed.Counter == PlayerAnimations.EffectAnimation->Speed.TargetUntilChange))
	{
		return;
	}
	if (PlayerAnimations.EffectAnimation->lastindex != 0)
	{

		EffectSprite->Texture = PlayerAnimations.EffectAnimation->Textures[PlayerAnimations.EffectAnimation->lastindex - 1];
		PlayerAnimations.EffectAnimation->lastindex++;

		if (PlayerAnimations.EffectAnimation->lastindex >= PlayerAnimations.EffectAnimation->Textures.size() + 1)
		{
			PlayerAnimations.EffectAnimation->lastindex = 0;
		}

		PlayerAnimations.EffectAnimation->Speed.Counter = 0;
		return;
	}
	if (PlayerAnimations.EffectAnimation->lastindex == 0)
	{
		EffectSprite->Texture = PlayerAnimations.EffectAnimation->PlainTexture;
	}
	PlayerAnimations.EffectAnimation->Speed.Counter = 0;
	PlayerAnimations.EffectAnimation->lastindex++;
}

void Player::HandleProjectileFiring(Game* game)
{
	if (PlayerSprite->Movement.CurrentState == Attack && PlayerAnimations.CharacterAnimation->lastindex == 0)
	{
		Projectile Projectile(PlayerSprite->Movement.Position.x, PlayerSprite->Movement.Position.y, ProjectileType::Bullet, PlayerSprite->Movement.CurrentDirection, 10, &game->SpriteList);
		game->ProjectileList.push_back(Projectile);
	}
}

void Player::UpdatePlayerAnimation(Game* game)
{
	UpdatePlayerCharacterAnimation(game);
	UpdatePlayerCostumeAnimation(game);
	UpdatePlayerEquipmentAnimation(game);
	UpdatePlayerEffectAnimation(game);
	HandleProjectileFiring(game);
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
}
