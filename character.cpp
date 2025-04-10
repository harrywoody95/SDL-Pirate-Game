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

void UpdateCharacterHitbox(Character* character)
{
	character->HitBox = character->Collision;
	//character->HitBox.Left = character->PlayerSprite->Movement.Position.x;
	//character->HitBox.Top = character->PlayerSprite->Movement.Position.y;
	//character->HitBox.Right = character->PlayerSprite->Movement.Position.x + (character->PlayerSprite->BitSize * character->PlayerSprite->Scale);
	//character->HitBox.Bottom = character->PlayerSprite->Movement.Position.y + (character->PlayerSprite->BitSize * character->PlayerSprite->Scale);
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
			Vec2 velocity = DirectionToVelocity(character->PlayerSprite->Movement.CurrentDirection);
			Vec2 ProjectilePosition = {0,0};

			if (velocity.x == 1)
			{
				ProjectilePosition.x = character->PlayerSprite->Movement.Position.x + (character->PlayerSprite->BitSize * character->PlayerSprite->Scale - 40);
			}
			else if (velocity.x == -1)
			{
				ProjectilePosition.x = character->PlayerSprite->Movement.Position.x - (character->PlayerSprite->BitSize * character->PlayerSprite->Scale - 40);
			}
			else {
				ProjectilePosition.x = character->PlayerSprite->Movement.Position.x;
			}

			if (velocity.y == 1)
			{
				ProjectilePosition.y = character->PlayerSprite->Movement.Position.y + (character->PlayerSprite->BitSize * character->PlayerSprite->Scale - 40);
			}
			else if (velocity.y == -1)
			{
				ProjectilePosition.y = character->PlayerSprite->Movement.Position.y - (character->PlayerSprite->BitSize * character->PlayerSprite->Scale - 40);
			}
			else {
				ProjectilePosition.y = character->PlayerSprite->Movement.Position.y;
			}


			Entity* Projectile = CreateProjectile(ProjectilePosition.x, ProjectilePosition.y, ProjectileType::Bullet, character->PlayerSprite->Movement.CurrentDirection, 10, game);
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
