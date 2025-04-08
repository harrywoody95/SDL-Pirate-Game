#include "Character.h"
#include "Game.h"
bool CanFireGun = true;

void UpdateCharacterCollision(Character* character)
{
	character->Collision.Left = (character->PlayerSprite->Movement.Position.x + ((character->PlayerSprite->BitSize * character->PlayerSprite->Scale) * CharacterCollisionBoxScale.Left ));
	character->Collision.Top = (character->PlayerSprite->Movement.Position.y + ((character->PlayerSprite->BitSize * character->PlayerSprite->Scale) * CharacterCollisionBoxScale.Top));

	character->Collision.Bottom = (character->PlayerSprite->Movement.Position.y + ((character->PlayerSprite->BitSize * character->PlayerSprite->Scale) - 
		((character->PlayerSprite->BitSize * character->PlayerSprite->Scale) * CharacterCollisionBoxScale.Bottom)));

	character->Collision.Right = (character->PlayerSprite->Movement.Position.x + ((character->PlayerSprite->BitSize * character->PlayerSprite->Scale) -
		((character->PlayerSprite->BitSize * character->PlayerSprite->Scale) * CharacterCollisionBoxScale.Right)));
	//character->Collision.Left = character->PlayerSprite->Movement.Position.x;
	//character->Collision.Top = character->PlayerSprite->Movement.Position.y;
	//character->Collision.Right = character->PlayerSprite->Movement.Position.x + (character->PlayerSprite->BitSize * character->PlayerSprite->Scale);
	//character->Collision.Bottom = character->PlayerSprite->Movement.Position.y + (character->PlayerSprite->BitSize * character->PlayerSprite->Scale);
}

void HandleCharacterProjectileFiring(Character* character, Game* game)
{
	//Player* Player = &game->PlayerEntity->Player;

	if (character->CurrentEquipment == nullptr || character->CurrentEquipment->Type == EquipmentType::Sword)
	{
		return;
	}

	if (CanFireGun)
	{
		if (character->PlayerSprite->Movement.CurrentState == Attack && character->PlayerAnimations.CharacterAnimation.lastindex == 2)
		{
			Entity* Projectile = CreateProjectile(character->PlayerSprite->Movement.Position.x, character->PlayerSprite->Movement.Position.y, ProjectileType::Bullet, character->PlayerSprite->Movement.CurrentDirection, 10, game);
			CanFireGun = false;
		}
	}
	else
	{
		if (character->PlayerAnimations.CharacterAnimation.lastindex != 2)
		{
			CanFireGun = true;
		}
	}
}

void UpdateAllCharacterAnimation(Game* game, Character* Character)
{
	UpdateCharacterAnimation(game, Character);
	UpdateCostumeAnimation(game, Character);
	UpdateEquipmentAnimation(game, Character);
	UpdateEffectAnimation(game, Character);
}
