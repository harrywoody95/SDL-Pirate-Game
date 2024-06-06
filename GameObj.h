#pragma once
#include"SDL.h"
#include"TextureManager.h"

class GameObject {
	int Xpos;
	int Ypos;
	SDL_Texture* Texture;
	SDL_Rect SourceBox, DestinationBox;

public:
	void CreateGameObject(const char* Filename, int Xpos, int Ypos);
	void Update();
	void Render();
};