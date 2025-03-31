#pragma once

enum class EquipmentType {
	None,
	Sword,
	Gun,
	Shovel,
};

struct Equipment {
	std::string Name;
	int DamageStat;
	EquipmentType Type;
};



// make a class for all equipment (swords, guns, shovel). this includes costumes (basic, adavnced)
//should be an item class!!