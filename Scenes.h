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
	bool isTransitioning = false;
	std::vector<Sprite*> Textures;
	int fade;
	void CreateScene(SceneType st, Game* game);
	void DrawScene(SceneType st, Game* game);
	void UpdateScene(SceneType st, Game* Game);
	void FadeIn(Game* Game);
	void FadeOut(Game* Game);
};
