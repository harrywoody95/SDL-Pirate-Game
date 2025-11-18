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
	bool Hostile = true;
	Character* Target = nullptr;
	PatrolRoute PatrolRoute;
	Direction* HostileDirection = nullptr;
	bool MoveBlocked =false;
	void UpdateNPC(Game* game);
	void NPCBoxCollision(Game* game);
	void UpdatePatrolRoute();
	void UpdateHostile(Game* game);
	int DeadBodyDisappearCounter = 0;
	bool PlayerInRange(Game* game, int Tollerence);
	void Die(Game* game);
	bool LineOfSight(Character* Target);
	void FaceTarget(Character* Target);
};


Entity* CreateNPC(float x, float y, Game* game);