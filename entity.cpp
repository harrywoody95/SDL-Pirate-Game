#include "Entity.h"
#include <vector>
#include "Game.h"
#include <iostream>

static int Nextid = 0;
Entity::Entity() {};
Entity::~Entity() {};

Entity* CreateEntity(float x, float y, Game* game, EntityType Type)
{
	Entity* entity = new Entity();

	entity->id = Nextid++;
	entity->Type = Type;

	switch (Type) {
	case EntityType::Player:
	{
		entity->Player = {};
		entity->Player.CreatePlayer(x, y, game, entity);
		break;
	}
	case EntityType::Projectile:
	{
		break;
	}
	case EntityType::Item:
	{
		break;
	}
	case EntityType::None:
	{
		break;
	}
	default:
	{
		std::cout << "ERROR CREATING ENTITY: NOT VALID ENTITY TYPE" << std::endl;
		break;
	}
	}

	game->EntityList.push_back(entity);

	return entity;
}

void UpdateEntities(Game* game)
{
	for (Entity* e : game->EntityList)
	{
		switch (e->Type) {
		case EntityType::Player:
		{
			e->Player.UpdatePlayer(game);
			break;
		}
		case EntityType::Projectile:
		{
			break;
		}
		case EntityType::Item:
		{
			break;
		}
		case EntityType::None:
		{
			break;
		}
		default:
		{
			std::cout << "ERROR UPDATING ENTITY: NOT VALID ENTITY TYPE" << std::endl;
			break;
		}
		}
	}
}