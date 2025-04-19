#include "Character.h"
#include "Game.h"
#include "Movement.h"
bool CanFireGun = true;
bool CanSwordSlash = true;
std::vector <Character*> NearbyCharacters(Game* game, Character* character);

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


			Entity* Projectile = CreateProjectile(ProjectilePosition.x, ProjectilePosition.y, ProjectileType::Bullet, character->PlayerSprite->Movement.CurrentDirection, character->CurrentEquipment->DamageStat, game);
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

void HandleCharacterSwordSlash(Character* character, Game* game)
{
	//Player* Player = &game->PlayerEntity->Player;

	if (character->CurrentEquipment == nullptr || character->CurrentEquipment->Type == EquipmentType::Gun)
	{
		return;
	}

	if (CanSwordSlash)
	{
		std::vector <Character*> CharactersToSlash = NearbyCharacters(game, character);
		if (character->PlayerSprite->Movement.CurrentState == Attack && character->PlayerAnimations.CharacterAnimation.lastindex == 2)
		{
			CanSwordSlash = false;
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
			CanSwordSlash = true;
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
}

bool CharacterFacingCharacter(Character* primaryCharacter, Character* secondaryCharacter)
{
	Vec2 PrimaryCharacterEntity = primaryCharacter->PlayerSprite->Movement.Position;
	Vec2 SeconaryCharacterEntity = secondaryCharacter->PlayerSprite->Movement.Position;
	int PrimaryCharacterDirection = primaryCharacter->PlayerSprite->Movement.CurrentDirection;
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
	if (PrimaryCharacter->PlayerSprite->Movement.Position.x == SecondaryCharacter->PlayerSprite->Movement.Position.x && PrimaryCharacter->PlayerSprite->Movement.Position.y == SecondaryCharacter->PlayerSprite->Movement.Position.y)
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
			IsCharacterCloseToCharacter(character->PlayerSprite->Movement.Position, AllCharactersList[x]->NPC.PlayerSprite->Movement.Position, 70) && 
			!IsSameCharacter(character, &AllCharactersList[x]->NPC))
		{
			CharactersToHitList.push_back(&AllCharactersList[x]->NPC);
		}
	}
	if (CharacterFacingCharacter(character, &game->PlayerEntity->Player) &&
		IsCharacterCloseToCharacter(character->PlayerSprite->Movement.Position, game->PlayerEntity->Player.PlayerSprite->Movement.Position, 70) &&
		!IsSameCharacter(character, &game->PlayerEntity->Player))
	{
		CharactersToHitList.push_back(&game->PlayerEntity->Player);
	}
	return CharactersToHitList;
}