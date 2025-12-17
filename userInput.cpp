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

void UserInput::HandleUserInput(Game* Game)
{
	Player* Player = &Game->PlayerEntity->Player;


	Player->Sprites.Body->Movement.Velocity.x = 0;
	Player->Sprites.Body->Movement.Velocity.y = 0;
	Player->Sprites.Body->Movement.LastDirection = Player->Sprites.Body->Movement.CurrentDirection;
	Player->Sprites.Body->Movement.LastState = Player->Sprites.Body->Movement.CurrentState;
	
	//pressed
	if (KEY_W_PRESSED)
	{
		Player->Sprites.Body->Movement.Velocity.y = -1;
		Player->Sprites.Body->Movement.CurrentDirection = North;
		Player->Sprites.Body->Movement.CurrentState = Walking;
	}
	else if (KEY_S_PRESSED)
	{
		Player->Sprites.Body->Movement.Velocity.y = 1;
		Player->Sprites.Body->Movement.CurrentDirection = South;
		Player->Sprites.Body->Movement.CurrentState = Walking;
	}
	else if (KEY_A_PRESSED)
	{
		Player->Sprites.Body->Movement.Velocity.x = -1;
		Player->Sprites.Body->Movement.CurrentDirection = West;
		Player->Sprites.Body->Movement.CurrentState = Walking;
	}
	else if (KEY_D_PRESSED)
	{
		Player->Sprites.Body->Movement.Velocity.x = 1;
		Player->Sprites.Body->Movement.CurrentDirection = East;
		Player->Sprites.Body->Movement.CurrentState = Walking;
	}

	if (KEY_LSHIFT_PRESSED)
	{
		Player->Sprites.Body->Movement.Speed = Player->Sprites.Body->Movement.RunningSpeed;
	}

	if (MOUSE_LBUTTON_PRESSED)
	{
		if (Player->CurrentEquipment != nullptr)
		{
			Player->Sprites.Body->Movement.CurrentState = Attack;
			Player->Sprites.Body->Movement.Speed = Player->Sprites.Body->Movement.AttackSpeed;
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
		Player->Sprites.Body->Movement.Speed = Player->Sprites.Body->Movement.WalkingSpeed;
	}
	if (MOUSE_LBUTTON_RELEASED)
	{
		Player->Sprites.Body->Movement.Speed = Player->Sprites.Body->Movement.WalkingSpeed;
	}

	//if idle
	if (!KEY_W_RELEASED && !KEY_W_PRESSED && !KEY_A_PRESSED && !KEY_A_RELEASED && !KEY_D_PRESSED && !KEY_D_RELEASED && !KEY_S_PRESSED && !KEY_S_RELEASED && !MOUSE_LBUTTON_PRESSED && !MOUSE_LBUTTON_RELEASED 
		||(MOUSE_LBUTTON_PRESSED && Player->CurrentEquipment == nullptr && !KEY_W_RELEASED && !KEY_W_PRESSED && !KEY_A_PRESSED && !KEY_A_RELEASED && !KEY_D_PRESSED && !KEY_D_RELEASED && !KEY_S_PRESSED && !KEY_S_RELEASED))
	{
		Player->Sprites.Body->Movement.CurrentState = Idle;
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
	
	if (BoxCollision(Player->Collision, CollisionBoxes, Player->Sprites.Body->Movement.Speed, &Player->Sprites.Body->Movement.CurrentDirection, Player->Sprites.Body->Movement.Velocity, &OutVelocity))
	{
		Player->Sprites.Body->Movement.Velocity = OutVelocity;
	}
}

void UserInput::Update(Game* Game)
{
	GetUserInput();
	HandleUserInput(Game);
}
