#pragma once
#include <string>
#include "Animation.h"
enum class CostumeType;
struct Costume
{

	int DefenceStat;
	CostumeType Type;
	Colour CostumeColour;

};

Colour StringToColour(std::string Colour);
CostumeType StringToCostumeType(std::string Type);