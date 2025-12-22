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
	Movement Movement;
	int Damage;
	Box HitBox;
};

Entity* CreateProjectile(float x, float y, ProjectileType Type, Direction Direction, int Damage, Game* game);
void UpdateProjectile(Game* game, Entity* Projectile);
void UpdateHitBox(Entity* Entity);
void HandleProjectileHit(Game* game, Entity* Projectile);
std::string GetProjectileFileName(ProjectileType Type, Direction Direction);
Vec2 DirectionToVelocity(Direction Direction);
