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
	//std::vector <Animation> AnimationList;
	PlayerAnimation PlayerAnimations;
	int InventoryLimit = 5;
	//inventory vector
	//equiped equitment
	//equipped costume - move costume type into here i think

	// 1: fix animation, when holding up it changes weirdly when pressing left or right, same for every direction
	// 2: implement running - change speed of animation and player use shift to control it
	// 3: need to seperate costume animations from player animations - maybe make a PlayerAnimation class to hold player animation, costume animation and weapon animations
	// 4: create item class - basic, mainly just a name, will be super class to everything
	// 5: create equipment and costume class
	// 6: create inventory system
	// 7: create animations for jump, attack(sword, gun, dig), decide on swimming 

	//move this function to game
	void LoadAnimations(std::string FileName);

	void SetPlayerAnimation(Game* game);
	void SetPlayerCostumeAnimation(Game* game);
	void UpdatePlayerCharacterAnimation(Game* game);
	void UpdatePlayerCostumeAnimation(Game* game);
	void UpdatePlayer(Game* game);
	void UpdatePlayerAnimation(Game* game);
};


