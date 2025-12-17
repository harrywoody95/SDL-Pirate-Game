#pragma once
#include "Window.h"
#include "Renderer.h"
#include "SDL_image.h"
#include "TextureManager.h"
#include "Flags.h"
#include "SpriteList.h"
#include "UserInput.h"
#include "Audio.h"
#include "Camera.h"
#include <vector>
#include "Map.h"
#include "Entity.h"

struct Game {

	static SDL_Event Event;
	UserInput UserInput;
	Window Window;
	Renderer Renderer;
	Flags Flags;
	SpriteList SpriteList;
	AnimationList AnimationList;
	Entity* PlayerEntity;
	std::vector <Entity*> EntityList;
	Audio Audio;
	Camera Camera;
	Map Map;

	bool IsRunning = false;
	
	void CreateGame(const char* Title, int xpos, int ypos, int Width, int Height, bool Fullscreen);

	void LoadAnimations();

	void HandleWindowEvent();
	void Render();
	void UpdateGame();

	void DestroyGame();
};
