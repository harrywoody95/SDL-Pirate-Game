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


	// 1: implement running - change speed of animation and player use shift to control it
	// 2: create equipment
	// 3: create inventory system
	// 4: create animations for jump, attack(sword, gun, dig), decide on swimming 


	void UpdatePlayerCollision(Game* game);
	void HandleProjectileFiring(Game* game);
	void UpdatePlayer(Game* game);
	void UpdatePlayerAnimation(Game* game);
};


