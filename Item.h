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
	Costume* Costume = nullptr;
	Equipment* Equipment = nullptr;
};

Entity* CreateItem(std::string Name, int Worth, ItemType ItemType, Game* game);
