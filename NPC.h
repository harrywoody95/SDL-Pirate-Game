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
	Entity* Target = nullptr;
	PatrolRoute PatrolRoute;
	Direction* HostileDirection = nullptr;
	bool MoveBlocked =false;
	void UpdateNPC(Game* game, Entity* NPC);
	int DeadBodyDisappearCounter = 0;
};

bool PlayerInRange(Game* game, Entity* SearchingEntity, int Tollerence);
void Die(Game* game, Entity* e);
bool LineOfSight(Entity* Target, Entity* Attacker);
void FaceTarget(Entity* Target, Entity* Attacker);
void AttackTarget(Entity* Target, Entity* Attacker);
void NPCMoveInDirection(Direction direction, Entity* e);
void NPCBoxCollision(Game* Game, Entity* e);
void UpdatePatrolRoute(Game* game, Entity* Patroller);
void UpdateHostile(Game* game, Entity* e);
bool ScanforTarget(Game* game, Entity* Scanner, int range);


Entity* CreateNPC(float x, float y, Game* game);