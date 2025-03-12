#include "TextureManager.h"
#include "SDL_image.h"

SDL_Texture* TextureManager::LoadTexture(const char* Filename)
{
	SDL_Surface* surface = IMG_Load(Filename);
	SDL_Texture* Texture = SDL_CreateTextureFromSurface(Renderer::MainRenderer, surface);
	SDL_FreeSurface(surface);
	return Texture;
}

void TextureManager::Draw(SDL_Texture* Texture, SDL_Rect SourceBox, SDL_Rect DestinationBox)
{
	SDL_RenderCopy(Renderer::MainRenderer, Texture, &SourceBox, &DestinationBox);
}
