#pragma once
#include "SDL.h"
#include "Sprite.h"
#include <vector>
#include "Animation.h"
#include "Costume.h"
#include "Collision.h"

struct Game;

struct Player
{
	Sprite* PlayerSprite;
	Sprite* CostumeSprite;
	Sprite* EquipmentSprite;
	Sprite* EffectSprite;
	Costume* CurrentCostume = nullptr;
	Equipment* CurrentEquipment = nullptr;
	PlayerAnimation PlayerAnimations;
	int InventoryLimit = 5;
	Box Collision;
	//inventory vector
	//equiped equitment


	// 3: create inventory system
	// 4: create animations for jump, attack(sword, gun, dig), decide on swimming 

	void UpdatePlayer(Game* game);
};

Entity* CreatePlayer(float x, float y, Game* game);
