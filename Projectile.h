#pragma once
#include "sprite.h"

struct Entity;
struct Game;

enum class ProjectileType {
	Bullet,
	CannonBall,
};

struct Projectile {
	Sprite* ProjectileSprite;
	ProjectileType Type;
	int Damage;


};

Entity* CreateProjectile(float x, float y, ProjectileType Type, Direction Direction, int Damage, Game* game);
void UpdateProjectile(Entity* Entity);
std::string GetProjectileFileName(ProjectileType Type, Direction Direction);
Vec2 DirectionToVelocity(Direction Direction);
