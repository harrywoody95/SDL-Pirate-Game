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
#include "Performance.h"

struct Game {
	
	static SDL_Event Event;
	UserInput UserInput;
	Window Window;
	Renderer Renderer;
	Flags Flags;
	SpriteList SpriteList;
	std::vector <SpriteAnimation*> AnimationList;
	Entity* PlayerEntity;
	std::vector <Entity*> EntityList;
	Audio Audio;
	Camera Camera;
	Map Map;
	MapEditor Editor;
	Performance Performance;

	bool IsRunning = false;
	
	void CreateGame(const char* Title, int xpos, int ypos, int Width, int Height, bool Fullscreen);

	void AddAnimation(std::string& name, std::vector<SDL_Texture*>& textures, int fps);
	void LoadAnimations();
	void HandleWindowEvent();
	void Render();
	void UpdateGame();
	void DestroyGame();
};
