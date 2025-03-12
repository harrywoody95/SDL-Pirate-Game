#include "Renderer.h"

SDL_Renderer* Renderer::MainRenderer = nullptr;

void Renderer::InitRenderer(SDL_Window* Window)
{
  MainRenderer = SDL_CreateRenderer(Window, -1, 0);
}
