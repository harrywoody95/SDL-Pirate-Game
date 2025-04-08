#pragma once
#include "SDL.h"
#include "Character.h"
#include <vector>

struct Game;

struct Player : public Character
{
	int InventoryLimit = 5;

	// 3: create inventory system
	// 4: create animations for jump, attack(sword, gun, dig), decide on swimming 

	void UpdatePlayer(Game* game);
};

Entity* CreatePlayer(float x, float y, Game* game);
