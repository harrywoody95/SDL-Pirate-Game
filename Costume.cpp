#include "Animation.h"
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
	else
	{
		return Colour::Black;
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
	else
	{
		return CostumeType::None;
	}
}