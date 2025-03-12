#pragma once
#include "SDL.h"
#include "Vec2.h"

class Window {

	SDL_Window* MainWindow;
	Vec2 Resolution;

public:
	void InitWindow(const char* Title, int xpos, int ypos, int Width, int Height, bool Fullscreen);
	SDL_Window* GetWindow();
	Vec2 GetResolution();
};
