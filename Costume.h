#pragma once
#include <string>
enum CostumeType;
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