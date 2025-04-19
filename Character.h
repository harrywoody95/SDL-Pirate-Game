#pragma once
#include "Sprite.h"
#include "Animation.h"
#include "Collision.h"
struct Game;
struct Entity;
struct Character {
	int Health = 100;
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
void HandleCharacterSwordSlash(Character* character, Game* game);
void HandleCharacterSwordHit(Character* character, Equipment* item, Game* game);
void HandleCharacterProjectileHit(Character* character, Entity* projectile, Game* game);
void UpdateAllCharacterAnimation(Game* game, Character* Character);
