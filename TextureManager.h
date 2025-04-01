#pragma once
#include "SDL.h"

class TextureManager {
public:
	static SDL_Texture* LoadTexture(const char* Filename);
	static void Draw(SDL_Texture* Texture, SDL_Rect SourceBox, SDL_Rect DestinationBox);
};
