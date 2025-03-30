#include "Window.h"

void Window::InitWindow(const char* Title, int xpos, int ypos, int Width, int Height, bool Fullscreen)
{
	MainWindow = SDL_CreateWindow(Title, xpos, ypos, Width, Height, Fullscreen);
	Resolution.x = static_cast<float>(Width);
	Resolution.y = static_cast<float>(Height);
}

SDL_Window* Window::GetWindow()
{
	return MainWindow;
}

Vec2 Window::GetResolution()
{
	return Resolution;
}
