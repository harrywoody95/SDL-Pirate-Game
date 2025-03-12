#pragma once
#include "SDL.h"

struct Renderer {
	static SDL_Renderer *MainRenderer;

	void InitRenderer(SDL_Window* Window);
};
