#pragma once
#include "Window.h"
#include "Renderer.h"
#include "SDL_image.h"
#include "TextureManager.h"
#include "Flags.h"
#include "SpriteList.h"
#include "UserInput.h"
#include "Audio.h"
#include "Camera.h"
#include <vector>
#include "Map.h"
#include "Entity.h"
#include "Editor.h"

struct Game {
	//**** -------------------- KNOWN BUGS ------------------------ ****
	//effect sprites arent showing in the right position and stay on screen
	//need to move them out of entity anyway shouldnt matter why or who set the effect. just should know to play it at a certain position.
	static SDL_Event Event;
	UserInput UserInput;
	Window Window;
	Renderer Renderer;
	Flags Flags;
	SpriteList SpriteList;
	//AnimationList AnimationList;
	//change name to animation list when chnage over complete
	std::vector <SpriteAnimation*> AnimationList;
	Entity* PlayerEntity;
	std::vector <Entity*> EntityList;
	Audio Audio;
	Camera Camera;
	Map Map;
	Editor Editor;

	bool IsRunning = false;
	
	void CreateGame(const char* Title, int xpos, int ypos, int Width, int Height, bool Fullscreen);

	void LoadAnimations();

	void HandleWindowEvent();
	void Render();
	void UpdateGame();

	void DestroyGame();
};
