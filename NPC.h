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
	bool Hostile = false;
	PatrolRoute PatrolRoute;
	void UpdateNPC(Game* game);
	void NPCBoxCollision(Game* game);
	void UpdatePatrolRoute();
};


Entity* CreateNPC(float x, float y, Game* game);