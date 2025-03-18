#pragma once
#include <vector>
#include "SDL.h"
#include <string>

enum Direction;
enum State;
enum EquipmentType;
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
	int TargetUntilChange = 30;
	int Counter = 0;
};

struct Animation {
	
	Direction direction;
	State state;
	CostumeType costumeType;
	EquipmentType EquipmentType;
	std::vector <SDL_Texture*> CharacterTextures;
	std::vector <SDL_Texture*> CostumeTextures;
	std::vector <SDL_Texture*> EquitmentTexture;
	int lastindex;
	Speed Speed;

	Animation(std::string FileName, CostumeType CostumeType, State State, Direction Direction);
	//need a function to control animation speed based on running/walking etc
};

