#include "Entity.h"
#include <vector>
#include "Game.h"
#include <iostream>

static int Nextid = 0;

Entity::~Entity() {};

Entity* CreateEntity(float x, float y, Game* game, EntityType Type)
{
	Entity* entity = new Entity{};

	entity->id = Nextid++;
	entity->Type = Type;

	switch (entity->Type) {
	case EntityType::Player:
	{
		entity->Player = {};
		break;
	}
	case EntityType::Projectile:
	{
		entity->Projectile = {};
		entity->Movement.Position = { x,y };
		break;
	}
	case EntityType::Item:
	{
		entity->Item = {};
		break;
	}
	case EntityType::NPC:
	{
		entity->NPC = {};
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
		game->EntityList[x]->Movement.Update(game->EntityList[x]);
		UpdateSpritePosition(game->EntityList[x]);

		switch (game->EntityList[x]->Type) {
		case EntityType::Player:
		{
			game->EntityList[x]->Player.UpdatePlayer(game);
			break;
		}
		case EntityType::NPC:
		{
			game->EntityList[x]->NPC.UpdateNPC(game, game->EntityList[x]);
			break;
		}
		case EntityType::Projectile:
		{
			UpdateProjectile(game, game->EntityList[x]);
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

void DestroyEntity(Game* game, Entity* Entity)
{
	for (int x = 0; x < game->EntityList.size(); x++)
	{
		if (game->EntityList[x] == Entity)
		{
			game->EntityList.erase(game->EntityList.begin() + x);
			delete Entity;
		}
	}
}

std::vector<Entity*> GetEntitites(Game* game, EntityType Type)
{
	std::vector <Entity*> list;
	for (int x = 0; x < game->EntityList.size(); x++)
	{
		if (game->EntityList[x]->Type == Type)
		{
			list.push_back(game->EntityList[x]);
		}
	}
	return list;
}
