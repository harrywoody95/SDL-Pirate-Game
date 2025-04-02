#pragma once
#include "sprite.h"

enum class ProjectileType {
	Bullet,
	CannonBall,
};

struct Projectile {
	Sprite* ProjectileSprite;
	ProjectileType Type;
	int Damage;

	Projectile(float x, float y, ProjectileType Type, Direction Direction, int Damage, SpriteList* SpriteList);
};

std::string GetProjectileFileName(ProjectileType Type, Direction Direction);
Vec2 DirectionToVelocity(Direction Direction);
