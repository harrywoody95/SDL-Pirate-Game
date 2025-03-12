#pragma once
#include <vector>
#include "MapTile.h"
struct Map {
	std::vector <MapTile> LayerOne;
	std::vector <MapTile> LayerTwo;
	std::vector <MapTile> LayerThree;

	void DrawMap(Camera* camera);
	void LoadMap(const char* LayerOneFileName, const char* LayerTwoFilename, const char* LayerThreeFilename, MapTileAssets MTA);
};
