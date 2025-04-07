#pragma once
#include "Character.h"
struct NPC : public Character
{
	//path
	int health;
	void UpdateNPC(Game* game);
};


Entity* CreateNPC(float x, float y, Game* game);