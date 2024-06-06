#include "Window.h"

void Window::InitWindow(const char* Title, int xpos, int ypos, int Width, int Height, bool Fullscreen)
{
	MainWindow = SDL_CreateWindow(Title, xpos, ypos, Width, Height, Fullscreen);
}

SDL_Window* Window::GetWindow()
{
	return MainWindow;
}