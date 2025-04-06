#include "Equipment.h"

Equipment* CreateEquipment(EquipmentType Type, int Damage)
{
	Equipment* equipment = new Equipment();
	equipment->DamageStat = Damage;
	equipment->Type = Type;
	return equipment;
}