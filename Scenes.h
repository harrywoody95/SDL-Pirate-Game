#pragma once
#include <String>
#include <vector>
#include "Sprite.h"

enum SceneType {
	Mainmenu,
};
struct Game;
struct Scene {
	std::string Name;
	bool isTransitioning;
	std::vector<Sprite*> Textures;
	int fade;
	void CreateScene(SceneType st);
	void DrawScene(SceneType st);
	void UpdateScene(SceneType st, Game* Game);
	void FadeIn(Game* Game);
	void FadeOut(Game* Game);
};
void MainMenu(Game* Game);
void StartGame();
