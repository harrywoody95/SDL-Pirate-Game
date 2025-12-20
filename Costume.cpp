#include "Costume.h"

Colour StringToColour(std::string Colour) {
	if (Colour == "Black")
	{
		return Colour::Black;
	}
	if (Colour == "White")
	{
		return Colour::White;
	}
	if (Colour == "Blue")
	{
		return Colour::Blue;
	}
	if (Colour == "Green")
	{
		return Colour::Green;
	}
	if (Colour == "Yellow")
	{
		return Colour::Yellow;
	}
	if (Colour == "Red")
	{
		return Colour::Red;
	}
}

std::string ColourToString(Colour Colour) {
	if (Colour == Colour::Black)
	{
		return "Black";
	}
	if (Colour == Colour::White)
	{
		return "White";
	}
	if (Colour == Colour::Blue)
	{
		return "Blue";
	}
	if (Colour == Colour::Green)
	{
		return "Green";
	}
	if (Colour == Colour::Yellow)
	{
		return "Yellow";
	}
	if (Colour == Colour::Red)
	{
		return "Red";
	}
}

CostumeType StringToCostumeType(std::string Type) {
	if (Type == "Basic")
	{
		return CostumeType::Basic;
	}
	if (Type == "Advanced")
	{
		return CostumeType::Advanced;
	}
}

std::string CostumeTypeToString(CostumeType Type) {
	if (Type == CostumeType::Basic)
	{
		return "Basic";
	}
	if (Type == CostumeType::Advanced)
	{
		return "Advanced";
	}
}

Costume* CreateCostume(CostumeType Type, Colour Colour, int DefenceStat)
{
	Costume* costume = new Costume();
	costume->Colour = Colour;
	costume->Type = Type;
	costume->DefenceStat = DefenceStat;
	return costume;
}
