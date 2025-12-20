#include "Equipment.h"
#include <string>

Equipment* CreateEquipment(EquipmentType Type, int Damage)
{
	Equipment* equipment = new Equipment();
	equipment->DamageStat = Damage;
	equipment->Type = Type;
	return equipment;
}

std::string EquipmentTypeToString(EquipmentType type)
{
	if (type == EquipmentType::Sword)
	{
		return "Sword";
	}
	if (type == EquipmentType::Gun)
	{
		return "Gun";
	}
	if (type == EquipmentType::Shovel)
	{
		return "Shovel";
	}
}