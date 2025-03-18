#pragma once
#include <string>
#include "Costume.h"
enum ItemType {
	costume, 
	equipment,
};
struct Item {
	std::string Name;
	int Value;
	ItemType Type;
	Costume Costume;
	void CreateItem(std::string Name, int Worth, ItemType ItemType, int Defence, Colour Color, CostumeType CostumeType)
	{
		this->Name = Name;
		Value = Worth;
		Type = ItemType;
		if (ItemType == costume)
		{
			Costume.CostumeColour = Color;
			Costume.DefenceStat = Defence;
			Costume.Type = CostumeType;
		}

	}
};
