#pragma once
#include <vector>
#include "SDL.h"
#include <string>
#include "Equipment.h"
#include "Costume.h"

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

enum class EffectType {
	None,
	Gun,
	Sword,
	Shovel,
};

struct Animation {

	struct Speed
	{
		static const int FPS = 144;
		int TargetUntilChange = 30;
		int Counter = 0;
	};

	Direction direction = {};
	State state = {};
	Colour colour = {};
	CostumeType costumeType = CostumeType::None;
	EquipmentType equipmentType = EquipmentType::None;
	EffectType effectType = EffectType::None;
	std::vector <SDL_Texture*> Textures;
	int lastindex = 0;
	Speed Speed = {};

	Animation(std::string BasePath, std::string BaseFile, int frames, Direction Direction, State state);
	Animation(std::string BasePath, std::string BaseFile, int frames, Direction Direction, State state, EquipmentType EquipmentType);
	Animation(std::string BasePath, std::string BaseFile, int frames, Direction Direction, State State, CostumeType CostumeType, Colour Colour);
	Animation(std::string BasePath, std::string BaseFile, int frames, Direction Direction, State State, EquipmentType EquipmentType, CostumeType CostumeType, Colour Colour);
	Animation() {};

	//need a function to control animation speed based on running/walking etc
};

struct AnimationList {
	std::vector <Animation> CharacterAnimations;
	std::vector <Animation> CostumeAnimations;
	std::vector <Animation> EquipmentAnimations;
	std::vector <Animation> EffectAnimations;
};

struct PlayerAnimation {
	Animation CharacterAnimation;
	Animation CostumeAnimation;
};

EquipmentType StringToEquipmentType(std::string type);

