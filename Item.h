#pragma once
#include <string>
#include "Costume.h"
#include "Equipment.h"

struct Game;
struct Entity;

enum class ItemType {
	None, 
	Costume, 
	Equipment,
};

struct Item {
	std::string Name = "";
	int Value = 0;
	ItemType Type = ItemType::None;
	// **** can i use template instead of having a varible for all? ****
	Costume* Costume = nullptr;
	Equipment* Equipment = nullptr;
};

Entity* CreateItem(std::string Name, int Worth, ItemType ItemType, Game* game);
