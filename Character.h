#pragma once
#include "Sprite.h"
#include "Animation.h"
#include "Collision.h"

struct Game;
struct Entity;
struct Character {
	SDL_Texture* TransparentTexture;
	int Health = 100;
	CharacterSprites Sprites;
	Sprite* EffectSprite;
	Costume* CurrentCostume = nullptr;
	Equipment* CurrentEquipment = nullptr;
	Box Collision;
	Box HitBox;

	// **** can i move these or avoid using them? ****
	int GunCooldown = 0;
	bool CanAttack = true;
	bool BeenAttacked = false;
	int AttackCooldown = 0;

};
void UpdateCharacterCollision(Entity* character);
void UpdateCharacterHitbox(Character* character);
void HandleCharacterProjectileFiring(Entity* character, Game* game);
void HandleCharacterSwordSlash(Entity* character, Game* game);
void HandleCharacterSwordHit(Character* character, Equipment* item, Game* game);
void HandleCharacterProjectileHit(Character* character, Entity* projectile, Game* game);
void UpdateAllCharacterAnimation(Game* game, Entity* Character);
