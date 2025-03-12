#include "Animation.h"
#include<fstream>
#include "TextureManager.h"
#include "Player.h"

Animation::Animation(std::string FileName, CostumeType CostumeType, State State, Direction Direction)
{
	lastindex = 0;
	costumeType = CostumeType;
	direction = Direction;
	state = State;
	std::ifstream file(FileName);
	if (file.is_open())
	{
		bool costume = false;
		std::string line = "Assets/Player/";
		std::string temp = "";
		while (std::getline(file, temp))
		{
			if (temp == "#COSTUME")
			{
				costume = true;
				continue;
			}
			if (costume)
			{
				line += temp;
				const char* filetext = line.c_str();
				SDL_Texture* Texture = TextureManager::LoadTexture(filetext);
				CostumeTextures.push_back(Texture);
				temp = "";
				line = "Assets/Player/";
				continue;
			}
			line += temp;
			const char* filetext = line.c_str();
			SDL_Texture* Texture = TextureManager::LoadTexture(filetext);
			PlayerTextures.push_back(Texture);
			temp = "";
			line = "Assets/Player/";
		}
	}
	file.close();
}
