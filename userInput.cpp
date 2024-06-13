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
		default:
			break;
		}
	}
}

void UserInput::HandleUserInput(Game* Game)
{

	Game->Player.Sprite->Movement.Velocity.x = 0;
	Game->Player.Sprite->Movement.Velocity.y = 0;
	Game->Player.Sprite->Movement.LastDirection = Game->Player.Sprite->Movement.CurrentDirection;
	Game->Player.Sprite->Movement.LastState = Game->Player.Sprite->Movement.CurrentState;
	
	//pressed
	if (KEY_W_PRESSED)
	{
		Game->Player.Sprite->Movement.Velocity.y = -1;
		Game->Player.Sprite->Movement.CurrentDirection = North;
		Game->Player.Sprite->Movement.CurrentState = Walking;
	}
	if (KEY_A_PRESSED)
	{
		Game->Player.Sprite->Movement.Velocity.x = -1;
		Game->Player.Sprite->Movement.CurrentDirection = West;
		Game->Player.Sprite->Movement.CurrentState = Walking;
	}
	if (KEY_S_PRESSED)
	{
		Game->Player.Sprite->Movement.Velocity.y = 1;
		Game->Player.Sprite->Movement.CurrentDirection = South;
		Game->Player.Sprite->Movement.CurrentState = Walking;
	}
	if (KEY_D_PRESSED)
	{
		Game->Player.Sprite->Movement.Velocity.x = 1;
		Game->Player.Sprite->Movement.CurrentDirection = East;
		Game->Player.Sprite->Movement.CurrentState = Walking;
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

	//if idle
	if (!KEY_W_RELEASED && !KEY_W_PRESSED && !KEY_A_PRESSED && !KEY_A_RELEASED && !KEY_D_PRESSED && !KEY_D_RELEASED && !KEY_S_PRESSED && !KEY_S_RELEASED)
	{
		Game->Player.Sprite->Movement.CurrentState = Idle;
	}

}

void UserInput::Update(Game* Game)
{
	GetUserInput();
	HandleUserInput(Game);
}