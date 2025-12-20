#pragma once
#include <string>
enum class EquipmentType {
	None,
	Sword,
	Gun,
	Shovel,
};

struct Equipment {
	int DamageStat = 0;
	EquipmentType Type = EquipmentType::None;
};

Equipment* CreateEquipment(EquipmentType Type, int Damage);
std::string EquipmentTypeToString(EquipmentType type);