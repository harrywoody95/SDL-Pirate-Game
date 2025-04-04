#pragma once
#include "player.h"
#include "Item.h"
struct Game;
enum class EntityType {
	None,
	Player,
	Item,
};

struct Entity {
	static int Nextid;
	EntityType Type;
	int id;

	union {
		Player Player;
		Item Item;
	};
	Entity();
	~Entity();
};


void CreateEntity(Game* game);
void UpdateEntity(Game* game);
void DestroyEntity(Game* game, Entity* Entity);