#include "Player.h"
#include "game.h"
#include <fstream>
#include <iostream>

//bool CanFireGun = true;

Entity* CreatePlayer(float x, float y, Game* game)
{
	Entity* entity = CreateEntity(x, y, game, EntityType::Player);
	Player* Player = &entity->Player;
	Player->PlayerSprite = new Sprite();
	Player->PlayerSprite->CreateSprite(x, y, "Assets/Sprites/Character/transparent.png", 16, 4, &game->SpriteList);
	Player->CostumeSprite = new Sprite();
	Player->CostumeSprite->CreateSprite(x, y, "Assets/Sprites/Character/transparent.png", 16, 4, &game->SpriteList);
	Player->EquipmentSprite = new Sprite();
	Player->EquipmentSprite->CreateSprite(x, y, "Assets/Sprites/Character/transparent.png", 16, 4, &game->SpriteList);
	Player->EffectSprite = new Sprite();
	Player->EffectSprite->CreateSprite(x, y, "Assets/Sprites/Character/transparent.png", 16, 4, &game->SpriteList);
	Player->PlayerSprite->Name = "PlayerSprite";
	Player->CostumeSprite->Name = "CostumeSprite";
	Player->EquipmentSprite->Name = "EquipmentSprite";
	Player->EffectSprite->Name = "EffectSprite";
	SetPlayerAnimation(game, Player);
	SetCostumeAnimation(game, Player);
	SetEquipmentAnimation(game, Player);
	return entity;
}

void Player::UpdatePlayer(Game* game)
{
	UpdateCharacterCollision(this);
	UpdateCharacterHitbox(this);
	UpdateAllCharacterAnimation(game, this);
	HandleCharacterProjectileFiring(this, game);
	HandleCharacterSwordSlash(this, game);
}
