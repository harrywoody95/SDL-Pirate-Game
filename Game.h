#pragma once
#include "Window.h"
#include "Renderer.h"
#include "SDL_image.h"
#include "TextureManager.h"
#include "Flags.h"
struct Game {
	Window Window;
	Renderer Renderer;
	Flags Flags;
	//store arrray of maps? store the map im on?
	//store preloaded assets here? maybe under a asset class?
	bool IsRunning = false;

	void CreateGame(const char* Title, int xpos, int ypos, int Width, int Height, bool Fullscreen);
	void HandleWindowEvent();
	void Render();
	
	void UpdateGame();

	void DestroyGame();
};