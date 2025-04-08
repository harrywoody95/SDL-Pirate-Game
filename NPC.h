#pragma once
#include "Character.h"

struct PatrolRoute {
	std::vector <Direction> Route;
	int Currentindex = 0;
	int WaitTick = 300;
	int Counter = 0;
	Vec2 LastPosition;
};

struct NPC : public Character
{
	//path
	int health;
	PatrolRoute PatrolRoute;
	void UpdateNPC(Game* game);
	void UpdatePatrolRoute();
};


Entity* CreateNPC(float x, float y, Game* game);