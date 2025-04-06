#include "Item.h"
#include "Game.h"

Entity* CreateItem(std::string Name, int Worth, ItemType ItemType, Game* game)
{
	Entity* entity = CreateEntity(0.0f, 0.0f, game, EntityType::Item);
	Item* item = &entity->Item;
	item->Name = Name;
	item->Value = Worth;
	item->Type = ItemType;
	return entity;
}
