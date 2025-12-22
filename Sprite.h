#pragma once
#include "SDL.h"
#include <iostream>
#include "Movement.h"
#include <vector>
#include <string>
struct Camera;
struct SpriteList;
struct Entity;
struct Game;

struct SpriteAnimation
{
	std::string Name;
	std::vector <SDL_Texture*> Textures;
	int TickSpeed;
};

struct SpriteAnimationState
{
	SpriteAnimation* Animation;
	int CurrentTick;
	bool Loop;
	int CurrentFrameIndex;
};

struct Sprite
{
	SpriteAnimationState* Animation = nullptr;
	std::string Name;
	Vec2 Position = {0,0};
	SDL_Texture* Texture = nullptr;
	int Scale;
	int BitSize;
	// **** Move collision box into entity using it. NPC, Player etc. ****
	SDL_Rect CollisionBox = {};

	void CreateSprite(float x, float y, const char* Filename, int SpriteBitSize, int Scale, SpriteList* SpriteList);
	void DeleteSprite(SpriteList* SpriteList);

	void Update();
	void Draw(Camera* camera);
};

struct CharacterSprites
{
	Sprite* Body;
	Sprite* Costume;
	Sprite* Equipment;
};

void UpdateSpritePosition(Entity* e);


SpriteAnimation* CreateSpriteAnimation(std::string Name, std::vector <SDL_Texture*> Textures, int TickSpeed);
void StartSpriteAnimation(Game* game, Sprite* Sprite, std::string Name, bool Loop);
