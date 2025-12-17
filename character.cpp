#include "Character.h"
#include "Game.h"
#include "Movement.h"

std::vector <Character*> NearbyCharacters(Game* game, Entity* e);

void UpdateCharacterCollision(Entity* e)
{
	Character* character;
	if (e->Type == EntityType::Player)
	{
		character = &e->Player;
	}
	else if (e->Type == EntityType::NPC)
	{
		character = &e->NPC;
	}
	else
	{
		return;
	}

	character->Collision.Left = (e->Movement.Position.x + ((character->Sprites.Body->BitSize * character->Sprites.Body->Scale) * CharacterCollisionBoxScale.Left ));
	character->Collision.Top = (e->Movement.Position.y + ((character->Sprites.Body->BitSize * character->Sprites.Body->Scale) * CharacterCollisionBoxScale.Top));

	character->Collision.Bottom = (e->Movement.Position.y + ((character->Sprites.Body->BitSize * character->Sprites.Body->Scale) - 
		((character->Sprites.Body->BitSize * character->Sprites.Body->Scale) * CharacterCollisionBoxScale.Bottom)));

	character->Collision.Right = (e->Movement.Position.x + ((character->Sprites.Body->BitSize * character->Sprites.Body->Scale) -
		((character->Sprites.Body->BitSize * character->Sprites.Body->Scale) * CharacterCollisionBoxScale.Right)));
}

void UpdateCharacterHitbox(Character* character)
{
	character->HitBox = character->Collision;
}

void HandleCharacterProjectileFiring(Entity* e, Game* game)
{
	Character* character;
	if (e->Type == EntityType::Player)
	{
		character = &e->Player;
	}
	else if (e->Type == EntityType::NPC)
	{
		character = &e->NPC;
	}
	else
	{
		return;
	}

	if (character->CurrentEquipment == nullptr || character->CurrentEquipment->Type != EquipmentType::Gun)
	{
		return;
	}

	if (character->CanAttack)
	{
		if (e->Movement.CurrentState == Attack && character->PlayerAnimations.CharacterAnimation.lastindex == 2)
		{
			Vec2 velocity = DirectionToVelocity(e->Movement.CurrentDirection);
			Vec2 ProjectilePosition = {0,0};

			if (velocity.x == 1)
			{
				ProjectilePosition.x = e->Movement.Position.x + (character->Sprites.Body->BitSize * character->Sprites.Body->Scale - 40);
			}
			else if (velocity.x == -1)
			{
				ProjectilePosition.x = e->Movement.Position.x - (character->Sprites.Body->BitSize * character->Sprites.Body->Scale - 40);
			}
			else {
				ProjectilePosition.x = e->Movement.Position.x;
			}

			if (velocity.y == 1)
			{
				ProjectilePosition.y = e->Movement.Position.y + (character->Sprites.Body->BitSize * character->Sprites.Body->Scale - 40);
			}
			else if (velocity.y == -1)
			{
				ProjectilePosition.y = e->Movement.Position.y - (character->Sprites.Body->BitSize * character->Sprites.Body->Scale - 40);
			}
			else {
				ProjectilePosition.y = e->Movement.Position.y;
			}


			Entity* Projectile = CreateProjectile(ProjectilePosition.x, ProjectilePosition.y, ProjectileType::Bullet, e->Movement.CurrentDirection, character->CurrentEquipment->DamageStat, game);
			
			character->CanAttack = false;
			//Character->Movement.LastState = Character->Movement.CurrentState;
			//Character->Movement.CurrentState = Idle;
		}
	}
	else
	{
		
		if (character->PlayerAnimations.CharacterAnimation.lastindex != 2)
		{
			character->CanAttack = true;
		}
	}
}

void HandleCharacterSwordSlash(Entity* e, Game* game)
{
	Character* character;
	if (e->Type == EntityType::Player)
	{
		character = &e->Player;
	}
	else if (e->Type == EntityType::NPC)
	{
		character = &e->NPC;
	}
	else
	{
		return;
	}

	if (character->CurrentEquipment == nullptr || character->CurrentEquipment->Type != EquipmentType::Sword)
	{
		return;
	}

	if (character->CanAttack)
	{
		std::vector <Character*> CharactersToSlash = NearbyCharacters(game, e);
		if (e->Movement.CurrentState == Attack && character->PlayerAnimations.CharacterAnimation.lastindex == 2)
		{
			character->CanAttack = false;
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
			character->CanAttack = true;
		}
	}
}

void UpdateAllCharacterAnimation(Game* game, Entity* Character)
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

bool CharacterFacingCharacter(Entity* primaryCharacter, Entity* secondaryCharacter)
{
	Vec2 PrimaryCharacterEntity = primaryCharacter->Movement.Position;
	Vec2 SeconaryCharacterEntity = secondaryCharacter->Movement.Position;
	int PrimaryCharacterDirection = primaryCharacter->Movement.CurrentDirection;
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

bool IsSameCharacter(Entity* PrimaryCharacter, Entity* SecondaryCharacter)
{
	//if (PrimaryCharacter->Movement.Position.x == SecondaryCharacter->Movement.Position.x && PrimaryCharacter->Movement.Position.y == SecondaryCharacter->Movement.Position.y)
	//{
	//	if (PrimaryCharacter->Health == SecondaryCharacter->Health)
	//	{
	//		return true;
	//	}
	//}
	if (PrimaryCharacter->id == SecondaryCharacter->id)
	{
		return true;
	}
	return false;
}

std::vector <Character*> NearbyCharacters(Game* game, Entity* e)
{
	Character* character;
	if (e->Type == EntityType::Player)
	{
		character = &e->Player;
	}
	else if (e->Type == EntityType::NPC)
	{
		character = &e->NPC;
	}


	std::vector <Entity*> AllCharactersList = GetEntitites(game, EntityType::NPC);
	std::vector <Character*> CharactersToHitList;
	
	for (int x = 0; x < AllCharactersList.size(); x++)
	{
		if (CharacterFacingCharacter(e, AllCharactersList[x]) && 
			IsCharacterCloseToCharacter(e->Movement.Position, AllCharactersList[x]->Movement.Position, 70) && 
			!IsSameCharacter(e, AllCharactersList[x]))
		{
			CharactersToHitList.push_back(&AllCharactersList[x]->NPC);
		}
	}
	if (CharacterFacingCharacter(e, game->PlayerEntity) &&
		IsCharacterCloseToCharacter(e->Movement.Position, game->PlayerEntity->Movement.Position, 70) &&
		!IsSameCharacter(e, game->PlayerEntity))
	{
		CharactersToHitList.push_back(&game->PlayerEntity->Player);
	}
	return CharactersToHitList;
}