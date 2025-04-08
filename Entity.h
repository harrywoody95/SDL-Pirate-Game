#pragma once
#include "Player.h"
#include "Item.h"
#include "Projectile.h"
#include "NPC.h"

struct Game;
struct NoEntity {};

enum class EntityType {
	None,
	Player,
	NPC,
	Item,
	Projectile,
};

struct Entity {
	static int Nextid;
	EntityType Type;
	int id;

	union {
		NoEntity NoEntity;
		Player Player;
		NPC NPC;
		Item Item;
		Projectile Projectile;
	};
	~Entity();
};


Entity* CreateEntity(float x, float y, Game* game, EntityType Type);
void UpdateEntities(Game* Game);
void DestroyEntity(Game* game, Entity* Entity);
std::vector<Entity*> GetEntitites(Game* game, EntityType Type);
