#pragma once
#include <string>
enum class CostumeType;
enum Colour {
	Black,
	Red,
	Blue,
	Green,
};

struct Costume {

	int DefenceStat;
	CostumeType Type;
	Colour CostumeColour;

};