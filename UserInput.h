#pragma once
#include "Vec2.h"
struct Game;

struct UserInput {

	bool KEY_W_PRESSED = false;
	bool KEY_A_PRESSED = false;
	bool KEY_S_PRESSED = false;
	bool KEY_D_PRESSED = false;
	bool KEY_LSHIFT_PRESSED = false;
	bool MOUSE_LBUTTON_PRESSED = false;

	bool KEY_W_RELEASED = false;
	bool KEY_A_RELEASED = false;
	bool KEY_S_RELEASED = false;
	bool KEY_D_RELEASED = false;
	bool KEY_LSHIFT_RELEASED = false;
	bool MOUSE_LBUTTON_RELEASED = false;

	Vec2i MousePos;

	void GetUserInput();
	void HandleUserInput(Game* Game);
	void Update(Game* Game);
};
