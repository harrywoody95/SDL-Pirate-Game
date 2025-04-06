#pragma once
#include <string>

enum class CostumeType {

	None,
	Basic,
	Advanced,
};

enum Colour {
	Black,
	White,
	Blue,
	Green,
	Yellow,
	Red,
};

struct Costume
{

	int DefenceStat;
	CostumeType Type = CostumeType::None;
	Colour CostumeColour;

};

Costume* CreateCostume(CostumeType Type, Colour Colour, int DefenceStat);
Colour StringToColour(std::string Colour);
CostumeType StringToCostumeType(std::string Type);
