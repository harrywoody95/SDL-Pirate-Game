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
		break;
	}
	case EntityType::Projectile:
	{
		entity->Projectile = {};
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
	for (int x = 0; x < game->EntityList.size(); x++)
	{
		switch (game->EntityList[x]->Type) {
		case EntityType::Player:
		{
			game->EntityList[x]->Player.UpdatePlayer(game);
			break;
		}
		case EntityType::Projectile:
		{
			UpdateProjectile(game->EntityList[x]);
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
