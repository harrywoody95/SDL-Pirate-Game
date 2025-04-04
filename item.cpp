#include "Item.h"

Item CreateItem(std::string Name, int Worth, ItemType ItemType)
{
	Item item;
	item.Name = Name;
	item.Value = Worth;
	item.Type = ItemType;
	return item;
}