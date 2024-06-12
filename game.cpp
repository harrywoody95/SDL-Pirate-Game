#include "Game.h"
#include <iostream>
#include "Map.h"

Map map;
SDL_Event Game::Event;

void Game::CreateGame(const char* Title, int xpos, int ypos, int Width, int Height, bool Fullscreen)
{
	int Flags = 0;
	if (Fullscreen)
	{
		Flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "SDL SUBSYSTEMS FAILED TO INITALISED" << std::endl;
		return;
	}
	std::cout << "SDL SUBSYSTEMS INITALISED" << std::endl;

	Window.InitWindow(Title, xpos, ypos, Width, Height, Flags);
	if (!Window.GetWindow())
	{
		std::cout << "SDL FAILED TO CREATE WINDOW" << std::endl;
		return;
	}
	std::cout << "SDL CREATED WINDOW" << std::endl;

	Renderer.InitRenderer(Window.GetWindow());
	if (!Renderer::MainRenderer)
	{
		std::cout << "SDL FAILED TO CREATE RENDERER" << std::endl;
		return;
	}
	std::cout << "SDL CREATED RENDERER" << std::endl;
	SDL_SetRenderDrawColor(Renderer::MainRenderer, 0, 0, 0, 255);
	IsRunning = true;
	MapTileAssets mapass;
	mapass.LoadMapTileAssets();
	map.LoadMap("Assets/Maps/Map1.txt", "", "", mapass);
	Player.Sprite = new Sprite();
	Player.Sprite->CreateSprite(0.0, 0.0, "Assets/Player/1.png", 16, 1, &SpriteList);
}

void Game::HandleWindowEvent()
{
	SDL_PollEvent(&Event);
	switch (Event.type)
	{
	case SDL_QUIT:
	{
		IsRunning = false;
		break;
	}
	default:
	{
		break;
	}
	}
}

void Game::Render()
{
	SDL_RenderClear(Renderer::MainRenderer);
	//add stuff to be rendered
	map.DrawMap();
	SpriteList.Draw();
	SDL_RenderPresent(Renderer::MainRenderer);
}

void Game::DestroyGame()
{
	SDL_DestroyWindow(Window.GetWindow());
	std::cout << "SDL DESTROYED WINDOW" << std::endl;
	SDL_DestroyRenderer(Renderer::MainRenderer);
	std::cout << "SDL DESTROYED RENDERER" << std::endl;
	SDL_Quit();
	std::cout << "GAME QUIT" << std::endl;

}

void Game::UpdateGame()
{
	UserInput.Update(this);
	SpriteList.Update();
}