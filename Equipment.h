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
