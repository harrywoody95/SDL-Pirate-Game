#pragma once
#include "Window.h"
#include "Renderer.h"
#include "SDL_image.h"
#include "TextureManager.h"
#include "Flags.h"
#include "SpriteList.h"
#include "UserInput.h"
#include "Player.h"
#include "Scenes.h"
#include "Audio.h"
#include <vector>
struct Game {

	static SDL_Event Event;
	UserInput UserInput;
	Window Window;
	Renderer Renderer;
	Flags Flags;
	SpriteList SpriteList;
	Player Player;
	std::vector <Scene> Scenes;
	Audio Audio;

	bool IsRunning = false;
	//store arrray of maps? store the map im on?
    //store preloaded assets here? maybe under a asset class?

	void CreateGame(const char* Title, int xpos, int ypos, int Width, int Height, bool Fullscreen);
	void HandleWindowEvent();
	void Render();
	
	void UpdateGame();

	void DestroyGame();
};