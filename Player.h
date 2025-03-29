#pragma once
#include "SDL.h"
#include "Sprite.h"
#include <vector>
#include "Animation.h"
#include "Costume.h"
struct Game;
struct Player
{
	Sprite* PlayerSprite;
	Sprite* CostumeSprite;
	Costume* CurrentCostume = nullptr;
	PlayerAnimation PlayerAnimations;
	int InventoryLimit = 5;
	//inventory vector
	//equiped equitment


	// 1: implement running - change speed of animation and player use shift to control it
	// 2: create equipment
	// 3: create inventory system
	// 4: create animations for jump, attack(sword, gun, dig), decide on swimming 


	void SetPlayerAnimation(Game* game);
	void SetPlayerCostumeAnimation(Game* game);
	void UpdatePlayerCharacterAnimation(Game* game);
	void UpdatePlayerCostumeAnimation(Game* game);
	void UpdatePlayer(Game* game);
	void UpdatePlayerAnimation(Game* game);
};


