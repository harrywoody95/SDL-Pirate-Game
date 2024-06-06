#include "Map.h"
#include <fstream>
#include <String>
#include <iostream>
#include "MapTile.h"
#include "TextureManager.h"

void Map::LoadMap(const char* LayerOneFileName, const char* LayerTwoFilename, const char* LayerThreeFilename, MapTileAssets MTA)
{
	SDL_Rect SourceBox, DesingationBox;
	SourceBox.w = 32;
	SourceBox.h = 32;
	SourceBox.x = 0;
	SourceBox.y = 0;
	DesingationBox.w = 32 * 2;
	DesingationBox.h = 32 * 2;
	DesingationBox.x = 0;
	DesingationBox.y = 0;

	std::ifstream file(LayerOneFileName);
	if (file.is_open())
	{
		int Row = 0;
		int Col = 0;
		std::string line = "";
		std::string data = "";
		int convertedData = 0;
		while (std::getline(file, line))
		{
			Col = 0;
			for (int x = 0; x < line.size(); x++)
			{
				DesingationBox.x = Col;
				DesingationBox.y = Row;
				if (line.at(x) == ',')
				{
					convertedData = stoi(data);
					MapTile MT;
					MT.CreateMapTile((MapTileType)convertedData, SourceBox, DesingationBox, MTA);
					LayerOne.push_back(MT);
					data = "";
					Col += 64;
				}
				else
				{
					data += line.at(x);
				}
				
			}
			Row += 64;
		}
		file.close();
	}
}

void Map::DrawMap()
{
	for (int index = 0; index < LayerOne.size(); index++)
	{
		TextureManager::Draw(LayerOne[index].Texture, LayerOne[index].SourceBox, LayerOne[index].DestinationBox);
	}
	for (int index = 0; index < LayerTwo.size(); index++)
	{
		TextureManager::Draw(LayerTwo[index].Texture, LayerTwo[index].SourceBox, LayerTwo[index].DestinationBox);
	}
	for (int index = 0; index < LayerThree.size(); index++)
	{
		TextureManager::Draw(LayerThree[index].Texture, LayerThree[index].SourceBox, LayerThree[index].DestinationBox);
	}
}