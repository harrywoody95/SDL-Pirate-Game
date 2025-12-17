#include "Player.h"
#include "game.h"
#include <fstream>
#include <iostream>

Entity* CreatePlayer(float x, float y, Game* game)
{
	Entity* entity = CreateEntity(x, y, game, EntityType::Player);
	Player* Player = &entity->Player;
	Player->Sprites.Body = new Sprite();
	Player->Sprites.Body->CreateSprite(x, y, "Assets/Sprites/Character/transparent.png", 16, 4, &game->SpriteList);
	Player->Sprites.Costume = new Sprite();
	Player->Sprites.Costume->CreateSprite(x, y, "Assets/Sprites/Character/transparent.png", 16, 4, &game->SpriteList);
	Player->Sprites.Equipment = new Sprite();
	Player->Sprites.Equipment->CreateSprite(x, y, "Assets/Sprites/Character/transparent.png", 16, 4, &game->SpriteList);
	Player->EffectSprite = new Sprite();
	Player->EffectSprite->CreateSprite(x, y, "Assets/Sprites/Character/transparent.png", 16, 4, &game->SpriteList);
	Player->Sprites.Body->Name = "Sprites.Body";
	Player->Sprites.Costume->Name = "Sprites.Costume";
	Player->Sprites.Equipment->Name = "Sprites.Equipment";
	Player->EffectSprite->Name = "EffectSprite";
	SetPlayerAnimation(game, Player);
	SetCostumeAnimation(game, Player);
	SetEquipmentAnimation(game, Player);
	return entity;
}

void Player::UpdatePlayer(Game* game)
{
	if (Health <= 0)
	{
		return;
	}
	UpdateCharacterCollision(this);
	UpdateCharacterHitbox(this);
	UpdateAllCharacterAnimation(game, this);
	HandleCharacterProjectileFiring(this, game);
	HandleCharacterSwordSlash(this, game);
}
