#include "Map.h"
#include <fstream>
#include <String>
#include <iostream>
#include "MapTile.h"
#include "TextureManager.h"

void Map::LoadMap(const char* LayerOneFileName, const char* LayerTwoFilename, const char* LayerThreeFilename, MapTileAssets MTA)
{

	std::ifstream file(LayerOneFileName);
	if (file.is_open())
	{
		int Row = 0;
		int Col = 0;
		std::string line = "";
		std::string data = "";
		int convertedData = 0;
		bool makeSolid = false;
		int count = 0;
		while (std::getline(file, line))
		{
			Col = 0;
			for (int x = 0; x < line.size(); x++)
			{
				count++;

				if (line.at(x) == ',')
				{
					if (count % 16 == 0)
					{
						makeSolid = true;
					}
					convertedData = stoi(data);
					MapTile MT;
					MT.CreateMapTile(Col, Row, (MapTileType)convertedData, 32, 2, MTA, makeSolid);
					LayerOne.push_back(MT);
					data = "";
					Col += 64;
					makeSolid = false;
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

void Map::DrawMap(Camera* camera)
{
	for (int index = 0; index < LayerOne.size(); index++)
	{
		LayerOne[index].Draw(camera);
	}
	for (int index = 0; index < LayerTwo.size(); index++)
	{
		LayerTwo[index].Draw(camera);
	}
	for (int index = 0; index < LayerThree.size(); index++)
	{
		LayerThree[index].Draw(camera);
	}
}
