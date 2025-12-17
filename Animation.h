#pragma once
#include <vector>
#include "SDL.h"
#include <string>
#include "Equipment.h"
#include "Costume.h"
#include "TextureManager.h"
#include <optional>

enum Direction;
enum State;
struct Game;
struct Entity;
struct Character;

// **** This should be characterstate ****
//**** Need animation type (costume, character, effect) and store that ****
// **** Animation are game engine. do i really need to know what the animation is? can i not just play all animations when needed? ****

//**** ANIMATION IS GAME ENGINE I SHOULD NOT CARE WHAT ANIMATION IS PLAYING **** 
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
	SDL_Texture* PlainTexture = TextureManager::LoadTexture(static_cast<const char*>("Assets/Sprites/Effects/transparent.png"));

	struct Speed
	{
		static const int FPS = 144;
		int TargetUntilChange = 30;
		int Counter = 0;
	};

	Direction direction = {};
	State state = {};
	Colour colour = {};
	// **** Can i use a template here as i know im getting a type of some sorts.. them use animation type to distinguish ****
	CostumeType costumeType = CostumeType::None;
	EquipmentType equipmentType = EquipmentType::None;
	EffectType effectType = EffectType::None;
	std::vector <SDL_Texture*> Textures;
	int lastindex = 0;
	Speed Speed = {};

	// **** anything else i can think of for this? seems a lot of the same ****
	Animation(std::string BasePath, std::string BaseFile, int frames, Direction Direction, State state);
	Animation(std::string BasePath, std::string BaseFile, int frames, Direction Direction, State state, EquipmentType EquipmentType);
	Animation(std::string BasePath, std::string BaseFile, int frames, Direction Direction, State State, CostumeType CostumeType, Colour Colour);
	Animation(std::string BasePath, std::string BaseFile, int frames, Direction Direction, State State, EquipmentType EquipmentType, CostumeType CostumeType, Colour Colour);
	Animation() {};

	void ResetAnimation();

	//need a function to control animation speed based on running/walking etc
};

void SetPlayerAnimation(Game* game, Entity* Character);
void SetCostumeAnimation(Game* game, Entity* Character);
void SetEquipmentAnimation(Game* game, Entity* Character);
void SetEffectAnimation(Game* game, Entity* Character);
void UpdateCharacterAnimation(Game* game, Entity* Character);
void UpdateCostumeAnimation(Game* game, Entity* Character);
void UpdateEquipmentAnimation(Game* game, Entity* Character);
void UpdateEffectAnimation(Game* game, Entity* Character);

struct AnimationList {
	std::vector <Animation> CharacterAnimations;
	std::vector <Animation> CostumeAnimations;
	std::vector <Animation> EquipmentAnimations;
	std::vector <Animation> EffectAnimations;
};

struct PlayerAnimation {
	Animation CharacterAnimation;
	std::optional<Animation> CostumeAnimation;
	std::optional<Animation> EquipmentAnimation;
	std::optional<Animation> EffectAnimation;
};

EquipmentType StringToEquipmentType(std::string type);
