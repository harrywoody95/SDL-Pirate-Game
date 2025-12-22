#include "Game.h"
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_sdl2.h"
#include "imgui/backends/imgui_impl_sdlrenderer2.h"
#include <iostream>
#include "SDL_mixer.h"
#include <fstream>
#include "DebugBox.h"
#include "Movement.h"
#include <array>


SDL_Event Game::Event;

//**** --- Animation Loading Helper Functions --- ****
std::vector<SDL_Texture*> LoadTextureSequence(std::string& basePath, std::string& fileName, int Frames);
void LoadCharacterAnimations(Game* game);
void LoadEquipmentAnimations(Game* game);
void LoadEffectAnimations(Game* game);
void LoadProjectileAnimations(Game* game);

void Game::CreateGame(const char* Title, int xpos, int ypos, int Width, int Height, bool Fullscreen)
{

	int Flags = 0;
	if (Fullscreen)
	{
		Flags = SDL_WINDOW_FULLSCREEN;
	}
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
	LoadAnimations();
	IsRunning = true;

	//create and load map
	MapTileAssets mapass;
	mapass.LoadMapTileAssets();
	Map.LoadMap("Assets/Maps/Map1.txt", "", "", mapass);
	
	//create player
	PlayerEntity = CreatePlayer(0, 0, this);

	//create costume and equipment
	Entity* costume = CreateItem("BlackBeard's Cloak", 250, ItemType::Costume, this);
	costume->Item.Costume = CreateCostume(CostumeType::Basic, Colour::Red, 20);

	Entity* npccostume = CreateItem("BlackBeard's skipper", 250, ItemType::Costume, this);
	npccostume->Item.Costume = CreateCostume(CostumeType::Basic, Colour::White, 5);

	Entity* Gun = CreateItem("BlackBeard's Gun", 500, ItemType::Equipment, this);
	Gun->Item.Equipment = CreateEquipment(EquipmentType::Gun, 50);

	Entity* sword = CreateItem("BlackBeard's sword", 500, ItemType::Equipment, this);
	sword->Item.Equipment = CreateEquipment(EquipmentType::Sword, 20);

	PlayerEntity->Player.CurrentCostume = costume->Item.Costume; 
	PlayerEntity->Player.CurrentEquipment = Gun->Item.Equipment;

	Entity* npc = CreateNPC(150, 150, this);
	npc->NPC.PatrolRoute.Route.push_back(Direction::East);
	npc->NPC.PatrolRoute.Route.push_back(Direction::West);
	npc->NPC.PatrolRoute.Route.push_back(Direction::West);
	npc->NPC.PatrolRoute.Route.push_back(Direction::East);
	npc->NPC.PatrolRoute.Route.push_back(Direction::North);
	npc->NPC.PatrolRoute.Route.push_back(Direction::South);
	npc->NPC.PatrolRoute.Route.push_back(Direction::South);
	npc->NPC.PatrolRoute.Route.push_back(Direction::North);
	npc->NPC.CurrentCostume = npccostume->Item.Costume;
	npc->NPC.CurrentEquipment = sword->Item.Equipment;

	//add music
	Audio.MusicList.AddMusic("Assets/Audio/Music/m.ogg", "MainMenu");
}

std::vector<SDL_Texture*> LoadTextureSequence(std::string& basePath, std::string& fileName, int Frames)
{
	std::vector<SDL_Texture*> textures;
	for (int i = 1; i <= Frames; i++)
	{
		std::string fullPath =
			basePath + fileName + "-" + std::to_string(i) + ".png";
		textures.push_back(TextureManager::LoadTexture(fullPath.c_str()));
	}
	return textures;
}

//Static arrays for Character animation loading.
static const std::array<std::string, 4> Directions = {
	"Down", "Up", "Right", "Left"
};

static const std::array<std::string, 4> States = {
	"Idle", "Walk", "Attack", "Dig"
};

static const std::array<std::string, 2> Equipments = {
	"Sword", "Gun"
};

static const std::array<std::string, 2> Costumes = {
	"Basic", "Advanced"
};

static const std::array<std::string, 6> Colours = {
	"Black", "White", "Blue", "Green", "Red", "Yellow"
};

void LoadCharacterAnimations(Game* game)
{
	std::string Path = "Assets/Sprites/Character/";

	for (std::string Direction : Directions)
	{
		for (std::string State : States)
		{
			if (State == "Idle")
			{
				std::string Name = Direction + "-Idle";
				std::vector <SDL_Texture*> Textures = LoadTextureSequence(Path, Name, 3);
				game->AddAnimation(Name, Textures, 30);
			}
			 
			if (State == "Walk")
			{
				std::string Name = Direction + "-Walk";
				std::vector <SDL_Texture*> Textures = LoadTextureSequence(Path, Name, 4);
				game->AddAnimation(Name, Textures, 30);
			}

			if (State == "Attack")
			{
				for (std::string equip : Equipments)
				{
					std::string Name = Direction + "-Attack-" + equip;
					std::vector <SDL_Texture*> Textures = LoadTextureSequence(Path, Name, 3);
					game->AddAnimation(Name, Textures, 30);
				}
			}

			if (State == "Dig" && (Direction == "Left" || Direction == "Right"))
			{
				std::string Name = Direction + "-Dig-Shovel";
				std::vector <SDL_Texture*> Textures = LoadTextureSequence(Path, Name, 3);
				game->AddAnimation(Name, Textures, 30);
			}
		}
	}

	// Player die
	{
		std::string Name = "Player-Die";
		std::vector <SDL_Texture*> Textures = LoadTextureSequence(Path, Name, 4);
		game->AddAnimation(Name, Textures, 30);
	}
}

void LoadCostumeAnimations(Game* game)
{
	std::string Path = "Assets/Sprites/Costumes/";

	for (std::string Direction : Directions)
	{
		for (std::string State : States)
		{
			if (State == "Idle" || State == "Walk")
			{
				for (std::string Costume : Costumes)
				{
					for (std::string Colour : Colours)
					{
						std::string Name = Direction + "-" + State + "-" + Costume + "-" + Colour;
						int EndFrame = (State == "Idle") ? 3 : 4;
						std::string BasePath = Path + Colour + "/";
						std::vector<SDL_Texture*> Textures = LoadTextureSequence(BasePath, Name, EndFrame);
						game->AddAnimation(Name, Textures, 30);
					}
				}
			}

			if (State == "Attack")
			{
				for (std::string Equipment : Equipments)
				{
					for (std::string Costume : Costumes)
					{
						for (std::string Colour : Colours)
						{
							std::string Name =Direction + "-Attack-" + Equipment + "-" + Costume + "-" + Colour;
							std::string BasePath = Path + Colour + "/";
							std::vector<SDL_Texture*> Textures = LoadTextureSequence(BasePath, Name, 3);
							game->AddAnimation(Name, Textures, 30);
						}
					}
				}
			}

			if (State == "Dig" && (Direction == "Left" || Direction == "Right"))
			{
				for (std::string Costume : Costumes)
				{
					for (std::string Colour : Colours)
					{
						std::string Name = Direction + "-Dig-Shovel-" + Costume + "-" + Colour;
						std::string BasePath = Path + Colour + "/";
						std::vector<SDL_Texture*> Textures = LoadTextureSequence(BasePath, Name, 3);
						game->AddAnimation(Name, Textures, 30);
					}
				}
			}
		}
	}

	// Costume player die
	for (std::string Costume : Costumes)
	{
		for (std::string Colour : Colours)
		{
			std::string Name = "Player-Die-" + Costume + "-" + Colour;
			std::string BasePath = Path + Colour + "/";
			std::vector<SDL_Texture*> Textures = LoadTextureSequence(BasePath, Name, 4);
			game->AddAnimation(Name, Textures, 30);
		}
	}
}

void LoadEquipmentAnimations(Game* game)
{
	std::string Path = "Assets/Sprites/Equipment/";

	for (std::string Direction : Directions)
	{
		for (std::string State : States)
		{
			if (State != "Idle" && State != "Walk")
				continue;
			int EndFrame = (State == "Idle") ? 3 : 4;
			for (std::string Equipment : Equipments)
			{
				std::string Name = Direction + "-" + State + "-" + Equipment;
				std::vector<SDL_Texture*> Textures = LoadTextureSequence(Path, Name, EndFrame);
				game->AddAnimation(Name, Textures, 30);
			}
		}
	}
}

void LoadEffectAnimations(Game* game)
{
	std::string Path = "Assets/Sprites/Effects/";

	for (std::string Direction : Directions)
	{
		for (std::string State : States)
		{
			if (State == "Attack")
			{
				for (std::string Equipment : Equipments)
				{
					std::string Name = Direction + "-Attack-" + Equipment + "-Effect";
					std::vector<SDL_Texture*> Textures = LoadTextureSequence(Path, Name, 2);
					game->AddAnimation(Name, Textures, 30);
				}
			}

			if (State == "Dig" && (Direction == "Left" || Direction == "Right"))
			{
				std::string Name = Direction + "-Dig-Shovel-Effect";
				std::vector<SDL_Texture*> Textures = LoadTextureSequence(Path, Name, 2);
				game->AddAnimation(Name, Textures, 30);
			}
		}
	}
}

void LoadProjectileAnimations(Game* game)
{
	std::string Path = "Assets/Sprites/Projectile/";

	for (std::string Direction : Directions)
	{
		std::vector<SDL_Texture*> Textures;
		std::string Name = Direction + "-Gun-Projectile";
		std::string FullPath = Path + Name + ".png";

		Textures.push_back(TextureManager::LoadTexture(FullPath.c_str()));
		game->AddAnimation(Name, Textures, 30);
	}
}

void Game::AddAnimation(std::string& name, std::vector<SDL_Texture*>& textures, int fps)
{
	AnimationList.push_back(CreateSpriteAnimation(name, textures, fps));
}

void Game::LoadAnimations()
{
	LoadCharacterAnimations(this);
	LoadCostumeAnimations(this);
	LoadEquipmentAnimations(this);
	LoadEffectAnimations(this);
	LoadProjectileAnimations(this);
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

		Map.DrawMap(&Camera);
		SpriteList.Draw(this);
		DrawCollsionBoxes(this);

		//imgui render

		if (Flags.EditorActive)
		{
			Editor.RenderEditor();
		}

		ImGui::Render();
		ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), this->Renderer.MainRenderer);
	

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
		UpdateEntities(this);
		UpdateCamera(&Camera, PlayerEntity);
		SpriteList.Update();
}
