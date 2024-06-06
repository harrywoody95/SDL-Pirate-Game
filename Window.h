#pragma once
#include "SDL.h"
class Window {

	SDL_Window* MainWindow;

public:
	void InitWindow(const char* Title, int xpos, int ypos, int Width, int Height, bool Fullscreen);
	SDL_Window* GetWindow();

};