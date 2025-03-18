#include "Game.h"
#include <iostream>
#include "Map.h"
#include "Scenes.h"
#include "SDL_mixer.h"
#include "Item.h"

Map map;
SDL_Event Game::Event;

void Game::CreateGame(const char* Title, int xpos, int ypos, int Width, int Height, bool Fullscreen)
{

	int Flags = 0;
	if (Fullscreen)
	{
		Flags = SDL_WINDOW_FULLSCREEN;
	}
	//SDL_setenv("SDL_AUDIODRIVER", "directsound", 1);
	//SDL_SetHint("SDL_AUDIODRIVER", "directsound");
	//init mixer
	if (SDL_Init(SDL_INIT_EVERYTHING | SDL_INIT_AUDIO) != 0)
	{
		std::cout << "SDL SUBSYSTEMS FAILED TO INITALISED" << std::endl;
		return;
	}
	//init mixer
	Mix_Init(0);

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

	//load all player animations
	Player.LoadAnimations("Assets/Player/Animations/master.txt");
	IsRunning = true;

	//create and load map
	MapTileAssets mapass;
	mapass.LoadMapTileAssets();
	map.LoadMap("Assets/Maps/Map1.txt", "", "", mapass);


	Item* item = new Item(CreateItem("BlackBeard's Cloak", 250, costume));
	item->Costume.DefenceStat = 20;
	item->Costume.CostumeColour = Colour::Black;
	item->Costume.Type = CostumeType::Advanced;

	Player.CurrentCostume = &item->Costume; 

	//create player sprite and set animation
	Player.PlayerSprite = new Sprite();
	Player.PlayerSprite->CreateSprite(1000.0, 1000.0, "Assets/Player/1.png", 16, 1, &SpriteList);
	Player.CostumeSprite = new Sprite();
	Player.CostumeSprite->CreateSprite(1000.0, 1000.0, "Assets/Player/transparent.png", 16, 1, &SpriteList);
	Player.PlayerSprite->Name = "PlayerSprite";
	Player.CostumeSprite->Name = "CostumeSprite";
	Player.SetPlayerAnimation();
	Player.SetPlayerCostumeAnimation();
	


	//create main menu
	Scene MainMenu;
	MainMenu.CreateScene(SceneType::Mainmenu, this);
	Scenes.push_back(MainMenu);

	//add music
	Audio.MusicList.AddMusic("Assets/Audio/Music/m.ogg", "MainMenu");
	
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
	if (Flags.MainMenu)
	{
		for (int x = 0; x < Scenes.size(); x++)
		{
			if (Scenes[x].Name == "MainMenu")
			{
				Scenes[x].DrawScene(SceneType::Mainmenu);
			}
		}
		SDL_RenderPresent(Renderer::MainRenderer);
	}
	else
	{
		map.DrawMap(&Camera);
		SpriteList.Draw();
		
		//SDL_Rect player_rect = {Camera.Position.x, Camera.Position.y, Camera.Size.x, Camera.Size.y };
		//SDL_RenderCopy(Renderer::MainRenderer, Player.Sprite->Texture,NULL, &player_rect);

		SDL_RenderPresent(Renderer::MainRenderer);
	}
	
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
	if (Flags.MainMenu)
	{
		for (int x = 0; x < Scenes.size(); x++)
		{
			if (Scenes[x].Name == "MainMenu")
			{
				Scenes[x].UpdateScene(SceneType::Mainmenu, this);
			}
		}
	}
	else
	{
		UserInput.Update(this);
		SpriteList.Update();
		Player.UpdatePlayer();
		UpdateCamera(&Camera, &Player);
	}
}
