#include "Animation.h"
#include<fstream>
#include "TextureManager.h"
#include "Player.h"

Animation::Animation(std::string FileName, State State, Direction Direction)
{
	lastindex = 0;
	direction = Direction;
	state = State;
	std::ifstream file(FileName);
	if (file.is_open())
	{
		bool costume = false;
		std::string line = "Assets/Sprites/";
		std::string temp = "";
		while (std::getline(file, temp))
		{

			line += temp;
			const char* filetext = line.c_str();
			SDL_Texture* Texture = TextureManager::LoadTexture(filetext);
			Textures.push_back(Texture);
			temp = "";
			line = "Assets/Sprites/";
		}
	}
	file.close();
}

Animation::Animation(std::string FileName, State State, Direction Direction, CostumeType CostumeType)
{
	lastindex = 0;
	direction = Direction;
	state = State;
	costumeType = CostumeType;
	std::ifstream file(FileName);
	if (file.is_open())
	{
		bool costume = false;
		std::string line = "Assets/Sprites/";
		std::string temp = "";
		while (std::getline(file, temp))
		{

			line += temp;
			const char* filetext = line.c_str();
			SDL_Texture* Texture = TextureManager::LoadTexture(filetext);
			Textures.push_back(Texture);
			temp = "";
			line = "Assets/Sprites/";
		}
	}
	file.close();
}

Animation::Animation(std::string FileName, State State, Direction Direction, EquipmentType EquipmentType)
{
	lastindex = 0;
	direction = Direction;
	state = State;
	equipmentType = EquipmentType;
	std::ifstream file(FileName);
	if (file.is_open())
	{
		bool costume = false;
		std::string line = "Assets/Player/";
		std::string temp = "";
		while (std::getline(file, temp))
		{

			line += temp;
			const char* filetext = line.c_str();
			SDL_Texture* Texture = TextureManager::LoadTexture(filetext);
			Textures.push_back(Texture);
			temp = "";
			line = "Assets/Player/";
		}
	}
	file.close();
}

EquipmentType StringToEquipmentType(std::string type)
{
	if (type == "Gun")
	{
		return EquipmentType::Gun;
	}
	if (type == "Sword")
	{
		return EquipmentType::Sword;
	}
	if (type == "Shovel")
	{
		return EquipmentType::Shovel;
	}
	else
	{
		return EquipmentType::None;
	}
}