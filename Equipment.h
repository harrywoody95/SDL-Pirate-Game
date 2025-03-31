#pragma once

enum class EquipmentType {
	None,
	Sword,
	Gun,
	Shovel,
};

struct Equipment {
	int DamageStat;
	EquipmentType Type = EquipmentType::None;
};



// make a class for all equipment (swords, guns, shovel). this includes costumes (basic, adavnced)
//should be an item class!!