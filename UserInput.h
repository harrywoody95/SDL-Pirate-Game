#pragma once
struct Game;
struct UserInput {

	bool KEY_W_PRESSED = false;
	bool KEY_A_PRESSED = false;
	bool KEY_S_PRESSED = false;
	bool KEY_D_PRESSED = false;

	bool KEY_W_RELEASED = false;
	bool KEY_A_RELEASED = false;
	bool KEY_S_RELEASED = false;
	bool KEY_D_RELEASED = false;

	void GetUserInput();
	void HandleUserInput(Game* Game);
	void Update(Game* Game);
};