#include "Projectile.h"
#include "Movement.h"
#include "SpriteList.h"
#include "Entity.h"
#include "Game.h"

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

void UpdateProjectile(Entity* Entity)
{

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