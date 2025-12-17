#pragma once
#include "Sprite.h"
#include "Animation.h"
#include "Collision.h"
struct Game;
struct Entity;
struct Character {
	int Health = 100;
	// **** Group together these sprite.. seperate effect sprites so not linked to character ****
	CharacterSprites Sprites;
	//Sprite* Sprites.Body;
	//Sprite* Sprites.Costume;
	//Sprite* Sprites.Equipment;
	Sprite* EffectSprite;

	Costume* CurrentCostume = nullptr;
	Equipment* CurrentEquipment = nullptr;
	PlayerAnimation PlayerAnimations;
	Box Collision;
	Box HitBox;

	// **** can i move these or avoid using them? ****
	int GunCooldown = 0;
	bool CanFireGun = true;
	bool CanSwordSlash = true;
	bool BeenAttacked = false;
};

void UpdateCharacterCollision(Character* character);
void UpdateCharacterHitbox(Character* character);
void HandleCharacterProjectileFiring(Character* character, Game* game);
void HandleCharacterSwordSlash(Character* character, Game* game);
void HandleCharacterSwordHit(Character* character, Equipment* item, Game* game);
void HandleCharacterProjectileHit(Character* character, Entity* projectile, Game* game);
void UpdateAllCharacterAnimation(Game* game, Character* Character);
