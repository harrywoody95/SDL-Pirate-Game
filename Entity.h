#pragma once
#include "player.h"
#include "Item.h"
#include "Projectile.h"
struct Game;
enum class EntityType {
	None,
	Player,
	Item,
	Projectile,
};
struct NoEntity {};
struct Entity {
	static int Nextid;
	EntityType Type;
	int id;

	union {
		NoEntity NoEntity;
		Player Player;
		Item Item;
		Projectile Projectile;
	};
	Entity();
	~Entity();
};


Entity* CreateEntity(float x, float y, Game* game, EntityType Type);
void UpdateEntities(Game* Game);
void DestroyEntity(Game* game, Entity* Entity);