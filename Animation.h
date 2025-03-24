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
enum class CostumeType {

	None,
	Basic,
	Advanced,
};

enum class EquipmentType {
	None,
	Sword,
	Gun,
	Shovel,
};

enum class EffectType {
	None,
	Gun,
	Sword,
	Shovel,
};

struct Speed
{
	static const int FPS = 144;
	int TargetUntilChange = 30;
	int Counter = 0;
};

struct Animation {

	Direction direction = {};
	State state = {};
	CostumeType costumeType = CostumeType::None;
	EquipmentType equipmentType = EquipmentType::None;
	EffectType effectType = EffectType::None;
	std::vector <SDL_Texture*> Textures;
	int lastindex = {};
	Speed Speed = {};

	Animation(std::string FileName, State State, Direction Direction);
	Animation(std::string FileName, State State, Direction Direction, CostumeType CostumeType);
	Animation(std::string FileName, State State, Direction Direction, EquipmentType EquipmentType);
	Animation() {};
	//need a function to control animation speed based on running/walking etc
};

struct AnimationList {
	std::vector <Animation*> CharacterAnimations;
	std::vector <Animation*> CostumeAnimations;
	std::vector <Animation*> EquipmentAnimations;
	std::vector <Animation*> EffectAnimations;
};

struct PlayerAnimation {
	Animation CharacterAnimation;
	Animation CostumeAnimation;
};

EquipmentType StringToEquipmentType(std::string type);

