#pragma once
#include <string>
#include "Costume.h"
#include "Equipment.h"

enum ItemType {
	costume, 
	equipment,
};

struct Item {
	std::string Name = {};
	int Value = {};
	ItemType Type = {};
	Costume Costume = {};
	Equipment Equipment = {};
};

Item CreateItem(std::string Name, int Worth, ItemType ItemType);
