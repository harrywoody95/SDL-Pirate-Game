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
	KEY_SHIFT_RELEASED = false;

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
			KEY_SHIFT_PRESSED = true;
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
			KEY_SHIFT_PRESSED = false;
			KEY_SHIFT_RELEASED = true;
			break;
		}
		default:
			break;
		}
	}
}

void UserInput::HandleUserInput(Game* Game)
{

	Game->Player.PlayerSprite->Movement.Velocity.x = 0;
	Game->Player.PlayerSprite->Movement.Velocity.y = 0;
	Game->Player.PlayerSprite->Movement.LastDirection = Game->Player.PlayerSprite->Movement.CurrentDirection;
	Game->Player.PlayerSprite->Movement.LastState = Game->Player.PlayerSprite->Movement.CurrentState;
	
	//pressed
	if (KEY_W_PRESSED)
	{
		Game->Player.PlayerSprite->Movement.Velocity.y = -1;
		Game->Player.PlayerSprite->Movement.CurrentDirection = North;
		Game->Player.PlayerSprite->Movement.CurrentState = Walking;
	}
	else if (KEY_A_PRESSED)
	{
		Game->Player.PlayerSprite->Movement.Velocity.x = -1;
		Game->Player.PlayerSprite->Movement.CurrentDirection = West;
		Game->Player.PlayerSprite->Movement.CurrentState = Walking;
	}
	else if (KEY_S_PRESSED)
	{
		Game->Player.PlayerSprite->Movement.Velocity.y = 1;
		Game->Player.PlayerSprite->Movement.CurrentDirection = South;
		Game->Player.PlayerSprite->Movement.CurrentState = Walking;
	}
	else if (KEY_D_PRESSED)
	{
		Game->Player.PlayerSprite->Movement.Velocity.x = 1;
		Game->Player.PlayerSprite->Movement.CurrentDirection = East;
		Game->Player.PlayerSprite->Movement.CurrentState = Walking;
	}

	if (KEY_SHIFT_PRESSED)
	{
		Game->Player.PlayerSprite->Movement.Speed = Game->Player.PlayerSprite->Movement.RunningSpeed;
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
	if (KEY_SHIFT_RELEASED)
	{
		Game->Player.PlayerSprite->Movement.Speed = Game->Player.PlayerSprite->Movement.WalkingSpeed;
	}

	//if idle
	if (!KEY_W_RELEASED && !KEY_W_PRESSED && !KEY_A_PRESSED && !KEY_A_RELEASED && !KEY_D_PRESSED && !KEY_D_RELEASED && !KEY_S_PRESSED && !KEY_S_RELEASED)
	{
		Game->Player.PlayerSprite->Movement.CurrentState = Idle;
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

	for (int x = 0; x < CollisionBoxes.size(); x++)
	{
		if (BoxesOverlap(Game->Player.Collision, CollisionBoxes[x]))
		{
			std::cout << "Box Collision" << std::endl;
		}
	}
}

void UserInput::Update(Game* Game)
{
	GetUserInput();
	HandleUserInput(Game);
}
