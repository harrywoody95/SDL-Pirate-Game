#pragma once
#include <vector>
#include "SDL.h"
#include <string>

enum Direction;
enum State;
enum AnimationType {
	IdleUp,
	IdleDown,
	IdleLeft,
	IdleRight,
	WalkUp,
	WalkDown,
	WalkLeft,
	WalkRight,
};
enum CostumeType {
	Plain,
	Basic,
	Advanced,
};

struct Speed
{
	static const int FPS = 144;
	int TargetUntilChange = 20;
	int ChangesPerSecond = 2;
	int Counter = 0;
};

struct Animation {
	
	Direction direction;
	State state;
	CostumeType costumeType;
	std::vector <SDL_Texture*> PlayerTextures;
	std::vector <SDL_Texture*> CostumeTextures;
	int lastindex;
	Speed Speed;

	Animation(std::string FileName, CostumeType CostumeType, State State, Direction Direction);
};

