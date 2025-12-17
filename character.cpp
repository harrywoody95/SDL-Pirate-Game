#include "Character.h"
#include "Game.h"
#include "Movement.h"

std::vector <Character*> NearbyCharacters(Game* game, Character* character);

void UpdateCharacterCollision(Character* character)
{
	character->Collision.Left = (character->Sprites.Body->Movement.Position.x + ((character->Sprites.Body->BitSize * character->Sprites.Body->Scale) * CharacterCollisionBoxScale.Left ));
	character->Collision.Top = (character->Sprites.Body->Movement.Position.y + ((character->Sprites.Body->BitSize * character->Sprites.Body->Scale) * CharacterCollisionBoxScale.Top));

	character->Collision.Bottom = (character->Sprites.Body->Movement.Position.y + ((character->Sprites.Body->BitSize * character->Sprites.Body->Scale) - 
		((character->Sprites.Body->BitSize * character->Sprites.Body->Scale) * CharacterCollisionBoxScale.Bottom)));

	character->Collision.Right = (character->Sprites.Body->Movement.Position.x + ((character->Sprites.Body->BitSize * character->Sprites.Body->Scale) -
		((character->Sprites.Body->BitSize * character->Sprites.Body->Scale) * CharacterCollisionBoxScale.Right)));
}

void UpdateCharacterHitbox(Character* character)
{
	character->HitBox = character->Collision;
}

void HandleCharacterProjectileFiring(Character* character, Game* game)
{
	if (character->CurrentEquipment == nullptr || character->CurrentEquipment->Type != EquipmentType::Gun)
	{
		return;
	}

	if (character->CanFireGun)
	{
		if (character->Sprites.Body->Movement.CurrentState == Attack && character->PlayerAnimations.CharacterAnimation.lastindex == 2)
		{
			Vec2 velocity = DirectionToVelocity(character->Sprites.Body->Movement.CurrentDirection);
			Vec2 ProjectilePosition = {0,0};

			if (velocity.x == 1)
			{
				ProjectilePosition.x = character->Sprites.Body->Movement.Position.x + (character->Sprites.Body->BitSize * character->Sprites.Body->Scale - 40);
			}
			else if (velocity.x == -1)
			{
				ProjectilePosition.x = character->Sprites.Body->Movement.Position.x - (character->Sprites.Body->BitSize * character->Sprites.Body->Scale - 40);
			}
			else {
				ProjectilePosition.x = character->Sprites.Body->Movement.Position.x;
			}

			if (velocity.y == 1)
			{
				ProjectilePosition.y = character->Sprites.Body->Movement.Position.y + (character->Sprites.Body->BitSize * character->Sprites.Body->Scale - 40);
			}
			else if (velocity.y == -1)
			{
				ProjectilePosition.y = character->Sprites.Body->Movement.Position.y - (character->Sprites.Body->BitSize * character->Sprites.Body->Scale - 40);
			}
			else {
				ProjectilePosition.y = character->Sprites.Body->Movement.Position.y;
			}


			Entity* Projectile = CreateProjectile(ProjectilePosition.x, ProjectilePosition.y, ProjectileType::Bullet, character->Sprites.Body->Movement.CurrentDirection, character->CurrentEquipment->DamageStat, game);
			
			character->CanFireGun = false;
			//Character->Sprites.Body->Movement.LastState = Character->Sprites.Body->Movement.CurrentState;
			//Character->Sprites.Body->Movement.CurrentState = Idle;
		}
	}
	else
	{
		
		if (character->PlayerAnimations.CharacterAnimation.lastindex != 2)
		{
			character->CanFireGun = true;
		}
	}
}

void HandleCharacterSwordSlash(Character* character, Game* game)
{
	//Player* Player = &game->PlayerEntity->Player;

	if (character->CurrentEquipment == nullptr || character->CurrentEquipment->Type != EquipmentType::Sword)
	{
		return;
	}

	if (character->CanSwordSlash)
	{
		std::vector <Character*> CharactersToSlash = NearbyCharacters(game, character);
		if (character->Sprites.Body->Movement.CurrentState == Attack && character->PlayerAnimations.CharacterAnimation.lastindex == 2)
		{
			character->CanSwordSlash = false;
			for (int x = 0; x < CharactersToSlash.size(); x++)
			{
				HandleCharacterSwordHit(CharactersToSlash[x], character->CurrentEquipment, game);
			}
		}
	}
	else
	{
		if (character->PlayerAnimations.CharacterAnimation.lastindex != 2)
		{
			character->CanSwordSlash = true;
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

void HandleCharacterProjectileHit(Character* character, Entity* projectile, Game* game)
{
	int DamageReduction = 0;
	if (character->CurrentCostume != nullptr)
	{
		DamageReduction = character->CurrentCostume->DefenceStat;
	}
	std::cout << "Projectile hit NPC" << std::endl;
	character->Health -= projectile->Projectile.Damage - DamageReduction;
	std::cout << character->Health << "/100" << std::endl;
	projectile->Projectile.ProjectileSprite->DeleteSprite(&game->SpriteList);
	DestroyEntity(game, projectile);
	character->BeenAttacked = true;
}

void HandleCharacterSwordHit(Character* character, Equipment* item, Game* game)
{
	int DamageReduction = 0;
	if (character->CurrentCostume != nullptr)
	{
		DamageReduction = character->CurrentCostume->DefenceStat;
	}
	std::cout << "Sword hit NPC" << std::endl;
	character->Health -= item->DamageStat - DamageReduction;
	std::cout << character->Health << "/100" << std::endl;
	character->BeenAttacked = true;
}

bool CharacterFacingCharacter(Character* primaryCharacter, Character* secondaryCharacter)
{
	Vec2 PrimaryCharacterEntity = primaryCharacter->Sprites.Body->Movement.Position;
	Vec2 SeconaryCharacterEntity = secondaryCharacter->Sprites.Body->Movement.Position;
	int PrimaryCharacterDirection = primaryCharacter->Sprites.Body->Movement.CurrentDirection;
	if (PrimaryCharacterDirection == West && PrimaryCharacterEntity.x > SeconaryCharacterEntity.x)
		return true;

	if (PrimaryCharacterDirection == East && PrimaryCharacterEntity.x < SeconaryCharacterEntity.x)
		return true;

	if (PrimaryCharacterDirection == North && PrimaryCharacterEntity.y > SeconaryCharacterEntity.y)
		return true;

	if (PrimaryCharacterDirection == South && PrimaryCharacterEntity.y < SeconaryCharacterEntity.y)
		return true;

	return false;
}

bool IsCharacterCloseToCharacter(Vec2 PrimaryCharacter, Vec2 SecondaryCharacter, int range)
{

	if (((PrimaryCharacter.x < SecondaryCharacter.x + range && PrimaryCharacter.x > SecondaryCharacter.x - range) && (PrimaryCharacter.y < SecondaryCharacter.y + range && PrimaryCharacter.y > SecondaryCharacter.y - range)))
		return true;
	else
		return false;
}

bool IsSameCharacter(Character* PrimaryCharacter, Character* SecondaryCharacter)
{
	if (PrimaryCharacter->Sprites.Body->Movement.Position.x == SecondaryCharacter->Sprites.Body->Movement.Position.x && PrimaryCharacter->Sprites.Body->Movement.Position.y == SecondaryCharacter->Sprites.Body->Movement.Position.y)
	{
		if (PrimaryCharacter->Health == SecondaryCharacter->Health)
		{
			return true;
		}
	}
	return false;
}

std::vector <Character*> NearbyCharacters(Game* game, Character* character)
{
	std::vector <Entity*> AllCharactersList = GetEntitites(game, EntityType::NPC);
	std::vector <Character*> CharactersToHitList;
	
	for (int x = 0; x < AllCharactersList.size(); x++)
	{
		if (CharacterFacingCharacter(character, &AllCharactersList[x]->NPC) && 
			IsCharacterCloseToCharacter(character->Sprites.Body->Movement.Position, AllCharactersList[x]->NPC.Sprites.Body->Movement.Position, 70) && 
			!IsSameCharacter(character, &AllCharactersList[x]->NPC))
		{
			CharactersToHitList.push_back(&AllCharactersList[x]->NPC);
		}
	}
	if (CharacterFacingCharacter(character, &game->PlayerEntity->Player) &&
		IsCharacterCloseToCharacter(character->Sprites.Body->Movement.Position, game->PlayerEntity->Player.Sprites.Body->Movement.Position, 70) &&
		!IsSameCharacter(character, &game->PlayerEntity->Player))
	{
		CharactersToHitList.push_back(&game->PlayerEntity->Player);
	}
	return CharactersToHitList;
}