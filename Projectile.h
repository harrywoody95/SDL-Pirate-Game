#pragma once
#include "sprite.h"
#include "Collision.h"

struct Entity;
struct Game;

enum class ProjectileType {
	Bullet,
	CannonBall,
};

struct Projectile {
	Sprite* ProjectileSprite;
	Entity* ShooterPtr;
	ProjectileType Type;
	int Damage;
	Box HitBox;


};

Entity* CreateProjectile(float x, float y, ProjectileType Type, Direction Direction, int Damage, Game* game);
void UpdateProjectile(Game* game, Entity* Entity);
void UpdateHitBox(Entity* Entity);
std::string GetProjectileFileName(ProjectileType Type, Direction Direction);
Vec2 DirectionToVelocity(Direction Direction);
