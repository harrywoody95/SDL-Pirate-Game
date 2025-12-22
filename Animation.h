#pragma once
#include <vector>
#include "SDL.h"
#include <string>
#include "Equipment.h"
#include "Costume.h"
#include "TextureManager.h"
#include <optional>

struct Game;
struct Entity;

void SetPlayerAnimation(Game* game, Entity* Character);
void SetCostumeAnimation(Game* game, Entity* Character);
void SetEquipmentAnimation(Game* game, Entity* Character);
void SetEffectAnimation(Game* game, Entity* Character);
void UpdateCharacterAnimation(Game* game, Entity* Character);
void UpdateCostumeAnimation(Game* game, Entity* Character);
void UpdateEquipmentAnimation(Game* game, Entity* Character);
void UpdateEffectAnimation(Game* game, Entity* Character);

EquipmentType StringToEquipmentType(std::string type);
