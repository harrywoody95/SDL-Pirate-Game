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

};
Item CreateItem(std::string Name, int Worth, ItemType ItemType)
{
	Item item;
	item.Name = Name;
	item.Value = Worth;
	item.Type = ItemType;
	return item;
}
