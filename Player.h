#pragma once
#include "SDL.h"
#include "Sprite.h"
#include <vector>
#include "Animation.h"

struct Player
{
	Sprite* Sprite;
	CostumeType costumeType = Basic;
	std::vector <Animation> AnimationList;
	Animation* CurrentAnimation;

	void LoadAnimations(std::string FileName);


	void SetAnimation();
	void UpdateAnimation();
	void UpdatePlayer();

	
};