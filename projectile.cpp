#include "Projectile.h"
#include "Movement.h"
#include "SpriteList.h"
#include "Entity.h"
#include "Game.h"

void RemoveDistantProjectile(Game* game, Entity* projectile);

Entity* CreateProjectile(float x, float y, ProjectileType Type, Direction Direction, int Damage, Game* game) {
	Entity* entity = CreateEntity(x, y, game, EntityType::Projectile);
	Projectile* Projectile = &entity->Projectile;
	Projectile->ProjectileSprite = new Sprite();
	Projectile->ProjectileSprite->CreateSprite(x, y, GetProjectileFileName(Type, Direction).c_str(), 16, 4, &game->SpriteList);
	Projectile->ProjectileSprite->Name = "Projectile";
	Projectile->ProjectileSprite->Movement.CurrentDirection = Direction;
	Projectile->Damage = Damage;
	Projectile->Type = Type;
	Projectile->ProjectileSprite->Movement.Velocity = DirectionToVelocity(Direction);
	Projectile->ProjectileSprite->Movement.Speed = Projectile->ProjectileSprite->Movement.ProjectileSpeed;
	return entity;
}

void UpdateProjectile(Game* game, Entity* projectile)
{
	UpdateHitBox(projectile);
	HandleProjectileHit(game, projectile);
	RemoveDistantProjectile(game, projectile);
}

void RemoveDistantProjectile(Game* game, Entity* projectile)
{
	int DestroyDistance = 1500;
	Vec2 ProjectilePosition = projectile->Projectile.ProjectileSprite->Movement.Position;
	Vec2 PlayerPosition = game->PlayerEntity->Player.Sprites.Body->Movement.Position;
	if (ProjectilePosition.x > PlayerPosition.x + DestroyDistance || ProjectilePosition.x < PlayerPosition.x - DestroyDistance ||
		ProjectilePosition.y > PlayerPosition.y + DestroyDistance || ProjectilePosition.y < PlayerPosition.y - DestroyDistance)
	{
		projectile->Projectile.ProjectileSprite->DeleteSprite(&game->SpriteList);
		DestroyEntity(game, projectile);
	}
}

void HandleProjectileHit(Game* game, Entity* projectile)
{
	//Player and NPC
	std::vector<Entity*> NPCList = GetEntitites(game, EntityType::NPC);
	for (int x = 0; x < NPCList.size(); x++)
	{
		if (BoxesOverlap(projectile->Projectile.HitBox, NPCList[x]->NPC.HitBox))
		{
			HandleCharacterProjectileHit(&NPCList[x]->NPC, projectile, game);
		}
	}
	if (BoxesOverlap(projectile->Projectile.HitBox, game->PlayerEntity->Player.HitBox))
	{
		HandleCharacterProjectileHit(&game->PlayerEntity->Player, projectile, game);
	}

	//ships?

}

void UpdateHitBox(Entity* Entity)
{
	Entity->Projectile.HitBox.Left = (Entity->Projectile.ProjectileSprite->Movement.Position.x + ((Entity->Projectile.ProjectileSprite->BitSize * Entity->Projectile.ProjectileSprite->Scale) * BulletHitBoxScale.Left));
	Entity->Projectile.HitBox.Top = (Entity->Projectile.ProjectileSprite->Movement.Position.y + ((Entity->Projectile.ProjectileSprite->BitSize * Entity->Projectile.ProjectileSprite->Scale) * BulletHitBoxScale.Top));

	Entity->Projectile.HitBox.Bottom = (Entity->Projectile.ProjectileSprite->Movement.Position.y + ((Entity->Projectile.ProjectileSprite->BitSize * Entity->Projectile.ProjectileSprite->Scale) -
		((Entity->Projectile.ProjectileSprite->BitSize * Entity->Projectile.ProjectileSprite->Scale) * BulletHitBoxScale.Bottom)));

	Entity->Projectile.HitBox.Right = (Entity->Projectile.ProjectileSprite->Movement.Position.x + ((Entity->Projectile.ProjectileSprite->BitSize * Entity->Projectile.ProjectileSprite->Scale) -
		((Entity->Projectile.ProjectileSprite->BitSize * Entity->Projectile.ProjectileSprite->Scale) * BulletHitBoxScale.Right)));
}

std::string GetProjectileFileName(ProjectileType Type, Direction Direction)
{
	std::string FileName = "Assets/Sprites/Projectile/";

	if (Direction == Direction::East)
	{
		FileName += "Right-";
	}
	if (Direction == Direction::West)
	{
		FileName += "Left-";
	}
	if (Direction == Direction::North)
	{
		FileName += "Up-";
	}
	if (Direction == Direction::South)
	{
		FileName += "Down-";
	}

	if (Type == ProjectileType::Bullet)
	{
		FileName += "Gun-";
	}
	if (Type == ProjectileType::CannonBall)
	{
		FileName += "CannonBall-";
	}

	FileName += "Projectile.png";
	return FileName.c_str();
}

Vec2 DirectionToVelocity(Direction Direction)
{
	Vec2 Velocity = { 0, 0 };
	if (Direction == Direction::East)
	{
		Velocity.x = 1;
	}
	if (Direction == Direction::West)
	{
		Velocity.x = -1;
	}
	if (Direction == Direction::North)
	{
		Velocity.y = -1;
	}
	if (Direction == Direction::South)
	{
		Velocity.y = 1;
	}
	return Velocity;
}
