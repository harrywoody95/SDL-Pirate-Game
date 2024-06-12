#include "UserInput.h"
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
	
	//pressed
	if (KEY_W_PRESSED)
	{
		Game->Player.Sprite->Movement.Velocity.y = -1;
	}
	if (KEY_A_PRESSED)
	{
		Game->Player.Sprite->Movement.Velocity.x = -1;
	}
	if (KEY_S_PRESSED)
	{
		Game->Player.Sprite->Movement.Velocity.y = 1;
	}
	if (KEY_D_PRESSED)
	{
		Game->Player.Sprite->Movement.Velocity.x = 1;
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

}

void UserInput::Update(Game* Game)
{
	GetUserInput();
	HandleUserInput(Game);
}