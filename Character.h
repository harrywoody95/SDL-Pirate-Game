#pragma once
#include "Sprite.h"
#include "Animation.h"
#include "Collision.h"
struct Game;
struct Character {
	Sprite* PlayerSprite;
	Sprite* CostumeSprite;
	Sprite* EquipmentSprite;
	Sprite* EffectSprite;
	Costume* CurrentCostume = nullptr;
	Equipment* CurrentEquipment = nullptr;
	PlayerAnimation PlayerAnimations;
	Box Collision;
	Box HitBox;
};

void UpdateCharacterCollision(Character* character);
void UpdateCharacterHitbox(Character* character);
void HandleCharacterProjectileFiring(Character* character, Game* game);
void UpdateAllCharacterAnimation(Game* game, Character* Character);
