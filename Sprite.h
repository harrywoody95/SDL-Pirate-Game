#pragma once
#include "SDL.h"
#include "Movement.h"
#include <vector>
#include <string>
struct Camera;
struct SpriteList;
struct Entity;
struct Sprite
{
	std::string Name;
	//Movement Movement;
	Vec2 Position = {0,0};
	//Vec2 Velocity = { 0,0 };
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
