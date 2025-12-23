#include "UserInput.h"
#include "SDL.h"
#include "Game.h"

void UserInput::GetUserInput()
{
	//reset all releases
	KEY_W_RELEASED = false;
	KEY_S_RELEASED = false;
	KEY_A_RELEASED = false;
	KEY_D_RELEASED = false;
	KEY_LSHIFT_RELEASED = false;
	MOUSE_LBUTTON_RELEASED = false;
	KEY_F5_RELEASED = false;
	KEY_F4_RELEASED = false;

	if (Game::Event.type == SDL_KEYDOWN)
	{
		switch (Game::Event.key.keysym.sym)
		{
		case SDLK_w:
		{
			KEY_W_PRESSED = true;
			break;
		}
		case SDLK_a:
		{
			KEY_A_PRESSED = true;
			break;
		}
		case SDLK_s:
		{
			KEY_S_PRESSED = true;
			break;
		}
		case SDLK_d:
		{
			KEY_D_PRESSED = true;
			break;
		}
		case SDLK_LSHIFT:
		{
			KEY_LSHIFT_PRESSED = true;
			break;
		}
		case SDLK_F5:
		{
			KEY_F5_PRESSED = true;
			break;
		}
		case SDLK_F4:
		{
			KEY_F4_PRESSED = true;
			break;
		}
		default:
			break;
		}
	}

	if (Game::Event.type == SDL_KEYUP)
	{
		switch (Game::Event.key.keysym.sym)
		{
		case SDLK_w:
		{
			KEY_W_PRESSED = false;
			KEY_W_RELEASED = true;
			break;
		}
		case SDLK_a:
		{
			KEY_A_PRESSED = false;
			KEY_A_RELEASED = true;
			break;
		}
		case SDLK_s:
		{
			KEY_S_PRESSED = false;
			KEY_S_RELEASED = true;
			break;
		}
		case SDLK_d:
		{
			KEY_D_PRESSED = false;
			KEY_D_RELEASED = true;
			break;
		}
		case SDLK_LSHIFT:
		{
			KEY_LSHIFT_PRESSED = false;
			KEY_LSHIFT_RELEASED = true;
			break;
		}
		case SDLK_F5:
		{
			KEY_F5_PRESSED = false;
			KEY_F5_RELEASED = true;
			break;
		}
		case SDLK_F4:
		{
			KEY_F4_PRESSED = false;
			KEY_F4_RELEASED = true;
			break;
		}
		default:
			break;
		}
	}

	if (Game::Event.type == SDL_MOUSEBUTTONDOWN)
	{
		switch (Game::Event.button.button)
		{
			case SDL_BUTTON_LEFT:
			{
				MOUSE_LBUTTON_PRESSED = true;
				break;
			}
			default:
			{
				break;
			}
		}
	}

	if (Game::Event.type == SDL_MOUSEBUTTONUP)
	{
		switch (Game::Event.button.button)
		{
			case SDL_BUTTON_LEFT:
			{
				MOUSE_LBUTTON_PRESSED = false;
				MOUSE_LBUTTON_RELEASED = true;
				break;
			}
			default:
			{
				break;
			}
		}
	}
}

void UserInput::HandleUserGameInput(Game* Game)
{
	Entity* Player = Game->PlayerEntity;


	Player->Movement.Velocity.x = 0;
	Player->Movement.Velocity.y = 0;
	Player->Movement.LastDirection = Player->Movement.CurrentDirection;
	Player->Movement.LastState = Player->Movement.CurrentState;
	
	//pressed
	if (KEY_W_PRESSED)
	{
		Player->Movement.Velocity.y = -1;
		Player->Movement.CurrentDirection = North;
		Player->Movement.CurrentState = Walking;
	}
	else if (KEY_S_PRESSED)
	{
		Player->Movement.Velocity.y = 1;
		Player->Movement.CurrentDirection = South;
		Player->Movement.CurrentState = Walking;
	}
	else if (KEY_A_PRESSED)
	{
		Player->Movement.Velocity.x = -1;
		Player->Movement.CurrentDirection = West;
		Player->Movement.CurrentState = Walking;
	}
	else if (KEY_D_PRESSED)
	{
		Player->Movement.Velocity.x = 1;
		Player->Movement.CurrentDirection = East;
		Player->Movement.CurrentState = Walking;
	}

	if (KEY_LSHIFT_PRESSED)
	{
		Player->Movement.Speed = Player->Movement.RunningSpeed;
	}

	if (MOUSE_LBUTTON_PRESSED)
	{
		if (Player->Player.CurrentEquipment != nullptr)
		{
			Player->Movement.CurrentState = Attack;
			Player->Movement.Speed = Player->Movement.AttackSpeed;
		}
	}

	//released
	if (KEY_W_RELEASED)
	{

	}
	if (KEY_A_RELEASED)
	{

	}
	if (KEY_S_RELEASED)
	{

	}
	if (KEY_D_RELEASED)
	{

	}
	if (KEY_LSHIFT_RELEASED)
	{
		Player->Movement.Speed = Player->Movement.WalkingSpeed;
	}
	if (MOUSE_LBUTTON_RELEASED)
	{
		Player->Movement.Speed = Player->Movement.WalkingSpeed;
	}
	if (KEY_F5_RELEASED)
	{
		Game->Flags.EditorActive = !Game->Flags.EditorActive;
	}
	if (KEY_F4_RELEASED)
	{
		Game->Flags.PerformanceActive = !Game->Flags.PerformanceActive;
	}

	//if idle
	if (!KEY_W_RELEASED && !KEY_W_PRESSED && !KEY_A_PRESSED && !KEY_A_RELEASED && !KEY_D_PRESSED && !KEY_D_RELEASED && !KEY_S_PRESSED && !KEY_S_RELEASED && !MOUSE_LBUTTON_PRESSED && !MOUSE_LBUTTON_RELEASED 
		||(MOUSE_LBUTTON_PRESSED && Player->Player.CurrentEquipment == nullptr && !KEY_W_RELEASED && !KEY_W_PRESSED && !KEY_A_PRESSED && !KEY_A_RELEASED && !KEY_D_PRESSED && !KEY_D_RELEASED && !KEY_S_PRESSED && !KEY_S_RELEASED))
	{
		Player->Movement.CurrentState = Idle;
	}

	std::vector <Box> CollisionBoxes;

	for (int x = 0; x < Game->Map.LayerOne.size(); x++)
	{
		if (Game->Map.LayerOne[x].Solid)
		{
			CollisionBoxes.push_back(Game->Map.LayerOne[x].Collision);
		}
	}
	for (int x = 0; x < Game->Map.LayerTwo.size(); x++)
	{
		if (Game->Map.LayerTwo[x].Solid)
		{
			CollisionBoxes.push_back(Game->Map.LayerTwo[x].Collision);
		}
	}
	for (int x = 0; x < Game->Map.LayerThree.size(); x++)
	{
		if (Game->Map.LayerThree[x].Solid)
		{
			CollisionBoxes.push_back(Game->Map.LayerThree[x].Collision);
		}
	}
	std::vector <Entity*> list = GetEntitites(Game, EntityType::NPC);
	for (int x = 0; x < list.size(); x++)
	{
		CollisionBoxes.push_back(list[x]->NPC.Collision);
	}

	Vec2 OutVelocity = { 0.0, 0.0 };
	
	if (BoxCollision(Player->Player.Collision, CollisionBoxes, Player->Movement.Speed, &Player->Movement.CurrentDirection, Player->Movement.Velocity, &OutVelocity))
	{
		Player->Movement.Velocity = OutVelocity;
	}
}

void UserInput::HandleUserEditorInput(Game* Game)
{
	
	Game->PlayerEntity->Movement.Velocity.x = 0;
	Game->PlayerEntity->Movement.Velocity.y = 0;
	Game->PlayerEntity->Movement.LastDirection = Game->PlayerEntity->Movement.CurrentDirection;
	Game->PlayerEntity->Movement.LastState = Game->PlayerEntity->Movement.CurrentState;

	//pressed
	if (KEY_W_PRESSED)
	{

	}
	else if (KEY_S_PRESSED)
	{

	}
	else if (KEY_A_PRESSED)
	{

	}
	else if (KEY_D_PRESSED)
	{

	}

	if (KEY_LSHIFT_PRESSED)
	{

	}

	if (MOUSE_LBUTTON_PRESSED)
	{

	}

	//released
	if (KEY_W_RELEASED)
	{

	}
	if (KEY_A_RELEASED)
	{

	}
	if (KEY_S_RELEASED)
	{

	}
	if (KEY_D_RELEASED)
	{

	}
	if (KEY_LSHIFT_RELEASED)
	{

	}
	if (MOUSE_LBUTTON_RELEASED)
	{

	}
	if (KEY_F5_RELEASED)
	{
		Game->Flags.EditorActive = !Game->Flags.EditorActive;
	}
	if (KEY_F4_RELEASED)
	{
		Game->Flags.PerformanceActive = !Game->Flags.PerformanceActive;
	}
}

void UserInput::HandleUserPerformanceInput(Game* Game)
{

	Game->PlayerEntity->Movement.Velocity.x = 0;
	Game->PlayerEntity->Movement.Velocity.y = 0;
	Game->PlayerEntity->Movement.LastDirection = Game->PlayerEntity->Movement.CurrentDirection;
	Game->PlayerEntity->Movement.LastState = Game->PlayerEntity->Movement.CurrentState;

	//pressed
	if (KEY_W_PRESSED)
	{

	}
	else if (KEY_S_PRESSED)
	{

	}
	else if (KEY_A_PRESSED)
	{

	}
	else if (KEY_D_PRESSED)
	{

	}

	if (KEY_LSHIFT_PRESSED)
	{

	}

	if (MOUSE_LBUTTON_PRESSED)
	{

	}

	//released
	if (KEY_W_RELEASED)
	{

	}
	if (KEY_A_RELEASED)
	{

	}
	if (KEY_S_RELEASED)
	{

	}
	if (KEY_D_RELEASED)
	{

	}
	if (KEY_LSHIFT_RELEASED)
	{

	}
	if (MOUSE_LBUTTON_RELEASED)
	{

	}
	if (KEY_F5_RELEASED)
	{
		Game->Flags.EditorActive = !Game->Flags.EditorActive;
	}
	if (KEY_F4_RELEASED)
	{
		Game->Flags.PerformanceActive = !Game->Flags.PerformanceActive;
	}
}

void UserInput::Update(Game* Game)
{
	GetUserInput();
	if (Game->Flags.EditorActive)
	{
		HandleUserEditorInput(Game);
	}
	//else if (Game->Flags.PerformanceActive)
	//{
	//	HandleUserPerformanceInput(Game);
	//}
	else
	{
		HandleUserGameInput(Game);
	}
}
