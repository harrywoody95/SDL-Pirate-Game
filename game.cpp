#include "Game.h"
#include <iostream>
#include "Scenes.h"
#include "SDL_mixer.h"
#include <fstream>
#include "DebugBox.h"


SDL_Event Game::Event;

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
	costume->Item.Costume = CreateCostume(CostumeType::Advanced, Colour::Green, 20);

	Entity* Gun = CreateItem("BlackBeard's Gun", 500, ItemType::Equipment, this);
	Gun->Item.Equipment = CreateEquipment(EquipmentType::Gun, 20);

	PlayerEntity->Player.CurrentCostume = costume->Item.Costume; 
	PlayerEntity->Player.CurrentEquipment = Gun->Item.Equipment;

	Entity* npc = CreateNPC(150, 150, this);

	//create main menu
	Scene MainMenu;
	MainMenu.CreateScene(SceneType::Mainmenu, this);
	Scenes.push_back(MainMenu);

	//add music
	Audio.MusicList.AddMusic("Assets/Audio/Music/m.ogg", "MainMenu");
}

void Game::LoadAnimations()
{
	
	//CHARACTER

	std::string Path = "Assets/Sprites/Character/";

	for (int Direction = 0; Direction < 4; Direction++)
	{
		std::string DirectionText = "";
		//set direction
		switch (Direction)
		{
		case 0:
			DirectionText = "Down";
			break;
		case 1:
			DirectionText = "Up";
			break;
		case 2:
			DirectionText = "Right";
			break;
		case 3:
			DirectionText = "Left";
			break;
		default: 
			return;
		}

		for (int State = 0; State < 4; State++)
		{
			std::string StateText = "";
			//set state
			switch (State)
			{
			case 0:
				StateText = "Idle";
				break;
			case 1:
				StateText = "Walk";
				break;
			case 2:
				StateText = "Attack";
				break;
			case 3:
				StateText = "Dig";
				break;
			default:
				return;
			}

			// IDLE/WALK CREATION
			if (StateText == "Walk")
			{
				std::string FileName = "";
				FileName = DirectionText + "-" + StateText;
				Animation a = Animation(Path, FileName, 4, StringToDirection(DirectionText), StringToState(StateText));
				AnimationList.CharacterAnimations.push_back(a);
			}
			if (StateText == "Idle")
			{
				std::string FileName = "";
				FileName = DirectionText + "-" + StateText;
				Animation a = Animation(Path, FileName, 3, StringToDirection(DirectionText), StringToState(StateText));
				AnimationList.CharacterAnimations.push_back(a);
			}
			// ATTACK CREATION
			if (StateText == "Attack")
			{
				for (int Equipment = 0; Equipment < 2; Equipment++)
				{
					//set equipment
					std::string EquipmentText = "";
					switch (Equipment)
					{
					case 0:
						EquipmentText = "Sword";
						break;
					case 1:
						EquipmentText = "Gun";
						break;
					default:
						return;

					}
					std::string FileName = "";
					FileName = DirectionText + "-" + StateText + "-" + EquipmentText;
					Animation a = Animation(Path, FileName, 3, StringToDirection(DirectionText), StringToState(StateText), StringToEquipmentType(EquipmentText));
					AnimationList.CharacterAnimations.push_back(a);
					//make files for attack gun and sword
				}
			}
			// DIG CREATION
			if (StateText == "Dig" && (DirectionText == "Left" || DirectionText == "Right"))
			{
				std::string Shovel = "Shovel";
				std::string FileName = "";
				FileName = DirectionText + "-" + StateText + "-" + Shovel;
				Animation a = Animation(Path, FileName, 3, StringToDirection(DirectionText), StringToState(StateText), StringToEquipmentType(Shovel));
				AnimationList.CharacterAnimations.push_back(a);
				//make files for dig shovel
			}

		}

	}

		std::string FileName = "";
		FileName = "Player-Die";
		Animation a = Animation(Path, FileName, 4, Direction::East, State::Dead);
		AnimationList.CharacterAnimations.push_back(a);
		//do player die here
	

	//COSTUME

	Path = "Assets/Sprites/Costumes/";

	for (int Direction = 0; Direction < 4; Direction++)
	{
		std::string DirectionText = "";
		//set direction
		switch (Direction)
		{
		case 0:
			DirectionText = "Down";
			break;
		case 1:
			DirectionText = "Up";
			break;
		case 2:
			DirectionText = "Right";
			break;
		case 3:
			DirectionText = "Left";
			break;
		default:
			return;
		}

		for (int State = 0; State < 4; State++)
		{
			std::string StateText = "";
			//set state
			switch (State)
			{
			case 0:
				StateText = "Idle";
				break;
			case 1:
				StateText = "Walk";
				break;
			case 2:
				StateText = "Attack";
				break;
			case 3:
				StateText = "Dig";
				break;
			default:
				return;
			}

			if (StateText == "Idle" || StateText == "Walk")
			{
				for (int Costume = 0; Costume < 2; Costume++)
				{
					//set costume type
					std::string CostumeText = "";
					switch (Costume)
					{
					case 0: 
						CostumeText = "Basic";
						break;
					case 1:
						CostumeText = "Advanced";
						break;
					default:
						return;
					}
					for (int Colour = 0; Colour < 6; Colour++)
					{
						//set colour
						std::string ColourText = "";
						switch (Colour)
						{
						case 0:
							ColourText = "Black";
							break;
						case 1:
							ColourText = "White";
							break;
						case 2:
							ColourText = "Blue";
							break;
						case 3:
							ColourText = "Green";
							break;
						case 4:
							ColourText = "Red";
							break;
						case 5:
							ColourText = "Yellow";
							break;

						}
						std::string FileName = "";
						std::string BasePath = Path + ColourText + "/";
						FileName = DirectionText + "-" + StateText + "-" + CostumeText + "-" + ColourText;
						if (StateText == "Idle")
						{
							Animation a = Animation(BasePath, FileName, 3, StringToDirection(DirectionText), StringToState(StateText), StringToCostumeType(CostumeText), StringToColour(ColourText));
							AnimationList.CostumeAnimations.push_back(a);
						}
						else
						{
							Animation a = Animation(BasePath, FileName, 4, StringToDirection(DirectionText), StringToState(StateText), StringToCostumeType(CostumeText), StringToColour(ColourText));
							AnimationList.CostumeAnimations.push_back(a);
							// make files for costumes idle or walk
						}
					}
				}
			}

			if (StateText == "Attack")
			{
				for (int Equipment = 0; Equipment < 2; Equipment++)
				{
					//set equipment
					std::string EquipmentText = "";
					switch (Equipment)
					{
					case 0:
						EquipmentText = "Sword";
						break;
					case 1:
						EquipmentText = "Gun";
						break;
					default:
						return;

					}
					for (int Costume = 0; Costume < 2; Costume++)
					{
						//set costume type
						std::string CostumeText = "";
						switch (Costume)
						{
						case 0:
							CostumeText = "Basic";
							break;
						case 1:
							CostumeText = "Advanced";
							break;
						default:
							return;
						}

						for (int Colour = 0; Colour < 6; Colour++)
						{
							//set colour
							std::string ColourText = "";
							switch (Colour)
							{
							case 0:
								ColourText = "Black";
								break;
							case 1:
								ColourText = "White";
								break;
							case 2:
								ColourText = "Blue";
								break;
							case 3:
								ColourText = "Green";
								break;
							case 4:
								ColourText = "Red";
								break;
							case 5:
								ColourText = "Yellow";
								break;

							}
							std::string FileName = "";
							std::string BasePath = Path + ColourText + "/";
							FileName = DirectionText + "-" + StateText + "-" + EquipmentText + "-" + CostumeText + "-" + ColourText;
							Animation a = Animation(BasePath, FileName, 3, StringToDirection(DirectionText), StringToState(StateText), StringToEquipmentType(EquipmentText), StringToCostumeType(CostumeText), StringToColour(ColourText));
							AnimationList.CostumeAnimations.push_back(a);
							//make files for attack gun and sword
						}
					}
				}
			}

			if (StateText == "Dig" && (DirectionText == "Left" || DirectionText == "Right"))
			{
				std::string Shovel = "Shovel";

				for (int Costume = 0; Costume < 2; Costume++)
				{
					//set costume type
					std::string CostumeText = "";
					switch (Costume)
					{
					case 0:
						CostumeText = "Basic";
						break;
					case 1:
						CostumeText = "Advanced";
						break;
					default:
						return;
					}

					for (int Colour = 0; Colour < 6; Colour++)
					{
						//set colour
						std::string ColourText = "";
						switch (Colour)
						{
						case 0:
							ColourText = "Black";
							break;
						case 1:
							ColourText = "White";
							break;
						case 2:
							ColourText = "Blue";
							break;
						case 3:
							ColourText = "Green";
							break;
						case 4:
							ColourText = "Red";
							break;
						case 5:
							ColourText = "Yellow";
							break;
						default:
							return;
						}
						std::string FileName = "";
						std::string BasePath = Path + ColourText + "/";
						FileName = DirectionText + "-" + StateText + "-" + Shovel + "-" + CostumeText + "-" + ColourText;
						Animation a = Animation(BasePath, FileName, 3, StringToDirection(DirectionText), StringToState(StateText), StringToEquipmentType(Shovel), StringToCostumeType(CostumeText), StringToColour(ColourText));
						AnimationList.CostumeAnimations.push_back(a);
						//make files for dig shovel
					}
				}
			}

		}

	}
	for (int CostumeType = 0; CostumeType < 2; CostumeType++)
	{
		//set costume type
		std::string CostumeText = "";
		switch (CostumeType)
		{
		case 0:
			CostumeText = "Basic";
			break;
		case 1:
			CostumeText = "Advanced";
			break;
		default:
			return;
		}

		for (int Colour = 0; Colour < 6; Colour++)
		{
			std::string ColourText = "";
			switch (Colour)
			{
			case 0:
				ColourText = "Black";
				break;
			case 1:
				ColourText = "White";
				break;
			case 2:
				ColourText = "Blue";
				break;
			case 3:
				ColourText = "Green";
				break;
			case 4:
				ColourText = "Red";
				break;
			case 5:
				ColourText = "Yellow";
				break;
			default:
				return;
			}
			std::string FileName = "";
			std::string BasePath = Path + ColourText + "/";
			FileName = "Player-Die-" + CostumeText + "-" + ColourText;
			Animation a = Animation(BasePath, FileName, 4, Direction::East, State::Dead);
			AnimationList.CostumeAnimations.push_back(a);
			//player die here

		}
	}

	//EQUIPMENT
	Path = "Assets/Sprites/Equipment/";

	for (int Direction = 0; Direction < 4; Direction++)
	{
		std::string DirectionText = "";
		//set direction
		switch (Direction)
		{
		case 0:
			DirectionText = "Down";
			break;
		case 1:
			DirectionText = "Up";
			break;
		case 2:
			DirectionText = "Right";
			break;
		case 3:
			DirectionText = "Left";
			break;
		default:
			return;
		}

		for (int State = 0; State < 4; State++)
		{
			std::string StateText = "";
			//set state
			switch (State)
			{
			case 0:
				StateText = "Idle";
				break;
			case 1:
				StateText = "Walk";
				break;
			case 2:
				StateText = "Attack";
				break;
			case 3:
				StateText = "Dig";
				break;
			default:
				return;
			}

			if (StateText == "Idle")
			{

				for (int Equipment = 0; Equipment < 2; Equipment++)
				{
					//set equipment
					std::string EquipmentText = "";
					switch (Equipment)
					{
					case 0:
						EquipmentText = "Sword";
						break;
					case 1:
						EquipmentText = "Gun";
						break;
					default:
						return;

					}
					std::string FileName = "";
					FileName = DirectionText + "-" + StateText + "-" + EquipmentText;
					Animation a = Animation(Path, FileName, 3, StringToDirection(DirectionText), StringToState(StateText), StringToEquipmentType(EquipmentText));
					AnimationList.EquipmentAnimations.push_back(a);
					//make files for equipment animations
				}
			}
			if (StateText == "Walk")
			{
				for (int Equipment = 0; Equipment < 2; Equipment++)
				{
					//set equipment
					std::string EquipmentText = "";
					switch (Equipment)
					{
					case 0:
						EquipmentText = "Sword";
						break;
					case 1:
						EquipmentText = "Gun";
						break;
					default:
						return;

					}
					std::string FileName = "";
					FileName = DirectionText + "-" + StateText + "-" + EquipmentText;
					Animation a = Animation(Path, FileName, 4, StringToDirection(DirectionText), StringToState(StateText), StringToEquipmentType(EquipmentText));
					AnimationList.EquipmentAnimations.push_back(a);
					//make files for equipment animations
				}
			}
		}
	}

	//EFFECTS

	Path = "Assets/Sprites/Effects/";

	for (int Direction = 0; Direction < 4; Direction++)
	{
		std::string DirectionText = "";
		//set direction
		switch (Direction)
		{
		case 0:
			DirectionText = "Down";
			break;
		case 1:
			DirectionText = "Up";
			break;
		case 2:
			DirectionText = "Right";
			break;
		case 3:
			DirectionText = "Left";
			break;
		default:
			return;
		}

		for (int State = 0; State < 4; State++)
		{
			std::string StateText = "";
			//set state
			switch (State)
			{
			case 0:
				StateText = "Idle";
				break;
			case 1:
				StateText = "Walk";
				break;
			case 2:
				StateText = "Attack";
				break;
			case 3:
				StateText = "Dig";
				break;
			default:
				return;
			}

			if (StateText == "Attack")
			{
				for (int Equipment = 0; Equipment < 2; Equipment++)
				{
					//set equipment
					std::string EquipmentText = "";
					switch (Equipment)
					{
					case 0:
						EquipmentText = "Sword";
						break;
					case 1:
						EquipmentText = "Gun";
						break;
					default:
						return;

					}
					std::string FileName = "";
					FileName = DirectionText + "-" + StateText + "-" + EquipmentText + "-Effect";
					Animation a = Animation(Path, FileName, 2, StringToDirection(DirectionText), StringToState(StateText), StringToEquipmentType(EquipmentText));
					AnimationList.EffectAnimations.push_back(a);
					//make files for sword/gun effect animations
				}

			}
			if (StateText == "Dig" && (DirectionText == "Left" || DirectionText == "Right"))
			{
				std::string FileName = "";
				FileName = DirectionText + "-" + StateText + "-" + "Shovel" + "-Effect";
				Animation a = Animation(Path, FileName, 2, StringToDirection(DirectionText), StringToState(StateText), StringToEquipmentType("Shovel"));
				AnimationList.EffectAnimations.push_back(a);
				//make files for shovel effect animations
			}
		}
	}
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
		Map.DrawMap(&Camera);
		SpriteList.Draw(this);
		DrawCollsionBoxes(this);
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
		UpdateEntities(this);
		UpdateCamera(&Camera, &PlayerEntity->Player);
	}
}
