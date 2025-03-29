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
			PlayerAnimations.CharacterAnimation = game->AnimationList.CharacterAnimations[x];
			PlayerSprite->Texture = PlayerAnimations.CharacterAnimation.Textures[0];
		}
	}
}
void Player::SetPlayerCostumeAnimation(Game* game)
{
	if (CurrentCostume->Type == CostumeType::None)
	{
		return;
	}
	for (int x = 0; x < game->AnimationList.CostumeAnimations.size(); x++)
	{
		if (game->AnimationList.CostumeAnimations[x].direction == PlayerSprite->Movement.CurrentDirection && 
			game->AnimationList.CostumeAnimations[x].state == PlayerSprite->Movement.CurrentState && 
			CurrentCostume->Type == game->AnimationList.CostumeAnimations[x].costumeType && 
			game->AnimationList.CostumeAnimations[x].colour == CurrentCostume->CostumeColour)
		{
			PlayerAnimations.CostumeAnimation = game->AnimationList.CostumeAnimations[x];
			CostumeSprite->Texture = PlayerAnimations.CostumeAnimation.Textures[0];
		}
	}
}

void Player::UpdatePlayerCharacterAnimation(Game* game)
{
	if(PlayerSprite->Movement.LastDirection != PlayerSprite->Movement.CurrentDirection || PlayerSprite->Movement.LastState != PlayerSprite->Movement.CurrentState)
	{
		SetPlayerAnimation(game);
	}
	PlayerAnimations.CharacterAnimation.Speed.Counter++;

	if (!(PlayerAnimations.CharacterAnimation.Speed.Counter == PlayerAnimations.CharacterAnimation.Speed.TargetUntilChange))
	{
		return;
	}

	PlayerSprite->Texture = PlayerAnimations.CharacterAnimation.Textures[PlayerAnimations.CharacterAnimation.lastindex];
	PlayerAnimations.CharacterAnimation.lastindex++;

	if (PlayerAnimations.CharacterAnimation.lastindex  >= PlayerAnimations.CharacterAnimation.Textures.size())
	{
		PlayerAnimations.CharacterAnimation.lastindex = 0;
	}

	PlayerAnimations.CharacterAnimation.Speed.Counter = 0;
	
}

void Player::UpdatePlayerCostumeAnimation(Game* game)
{
	if (PlayerSprite->Movement.LastDirection != PlayerSprite->Movement.CurrentDirection || PlayerSprite->Movement.LastState != PlayerSprite->Movement.CurrentState)
	{
		SetPlayerCostumeAnimation(game);
	}
	if (CurrentCostume == nullptr || CurrentCostume->Type == CostumeType::None)
	{
		return;
	}

	PlayerAnimations.CostumeAnimation.Speed.Counter++;

	if (!(PlayerAnimations.CostumeAnimation.Speed.Counter == PlayerAnimations.CostumeAnimation.Speed.TargetUntilChange))
	{
		return;
	}

	CostumeSprite->Texture = PlayerAnimations.CostumeAnimation.Textures[PlayerAnimations.CostumeAnimation.lastindex];
	PlayerAnimations.CostumeAnimation.lastindex++;

	if (PlayerAnimations.CostumeAnimation.lastindex >= PlayerAnimations.CostumeAnimation.Textures.size())
	{
		PlayerAnimations.CostumeAnimation.lastindex = 0;
	}

	PlayerAnimations.CostumeAnimation.Speed.Counter = 0;
	
}

void Player::UpdatePlayerAnimation(Game* game)
{
	UpdatePlayerCharacterAnimation(game);
	UpdatePlayerCostumeAnimation(game);
}

void Player::UpdatePlayer(Game* game)
{

	UpdatePlayerAnimation(game);
}
