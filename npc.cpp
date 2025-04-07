#include "NPC.h"
#include "Game.h"

//bool CanFireGun = true;

Entity* CreateNPC(float x, float y, Game* game)
{
	Entity* entity = CreateEntity(x, y, game, EntityType::NPC);
	NPC* NPC = &entity->NPC;
	NPC->PlayerSprite = new Sprite();
	NPC->PlayerSprite->CreateSprite(x, y, "Assets/Sprites/Character/transparent.png", 16, 4, &game->SpriteList);
	NPC->CostumeSprite = new Sprite();
	NPC->CostumeSprite->CreateSprite(x, y, "Assets/Sprites/Character/transparent.png", 16, 4, &game->SpriteList);
	NPC->EquipmentSprite = new Sprite();
	NPC->EquipmentSprite->CreateSprite(x, y, "Assets/Sprites/Character/transparent.png", 16, 4, &game->SpriteList);
	NPC->EffectSprite = new Sprite();
	NPC->EffectSprite->CreateSprite(x, y, "Assets/Sprites/Character/transparent.png", 16, 4, &game->SpriteList);
	NPC->PlayerSprite->Name = "PlayerSprite";
	NPC->CostumeSprite->Name = "CostumeSprite";
	NPC->EquipmentSprite->Name = "EquipmentSprite";
	NPC->EffectSprite->Name = "EffectSprite";
	SetPlayerAnimation(game, NPC);
	SetCostumeAnimation(game, NPC);
	SetEquipmentAnimation(game, NPC);
	return entity;
}

/*void HandleNPCProjectileFiring(Game* game)
{
	NPC* NPC = &game->PlayerEntity->NPC;

	if (NPC->CurrentEquipment == nullptr || NPC->CurrentEquipment->Type == EquipmentType::Sword)
	{
		return;
	}

	if (CanFireGun)
	{
		if (NPC->PlayerSprite->Movement.CurrentState == Attack && NPC->PlayerAnimations.CharacterAnimation->lastindex == 2)
		{
			Entity* Projectile = CreateProjectile(NPC->PlayerSprite->Movement.Position.x, NPC->PlayerSprite->Movement.Position.y, ProjectileType::Bullet, NPC->PlayerSprite->Movement.CurrentDirection, 10, game);
			CanFireGun = false;
		}
	}
	else
	{
		if (NPC->PlayerAnimations.CharacterAnimation->lastindex != 2)
		{
			CanFireGun = true;
		}
	}
}
*/

//void UpdateCharacterAnimation(Game* game, Character* Character)
//{
//	UpdateCharacterAnimation(game, Character);
//	UpdateCostumeAnimation(game, Character);
//	UpdateEquipmentAnimation(game, Character);
//	UpdateEffectAnimation(game, Character);
//}

//void UpdatePlayerCollision(Game* game)
//{
//	NPC* NPC = &game->PlayerEntity->NPC;
//
//	NPC->Collision.Left = NPC->PlayerSprite->Movement.Position.x;
//	NPC->Collision.Top = NPC->PlayerSprite->Movement.Position.y;
//	NPC->Collision.Right = NPC->PlayerSprite->Movement.Position.x + (NPC->PlayerSprite->BitSize * NPC->PlayerSprite->Scale);
//	NPC->Collision.Bottom = NPC->PlayerSprite->Movement.Position.y + (NPC->PlayerSprite->BitSize * NPC->PlayerSprite->Scale);
//}

void NPC::UpdateNPC(Game* game)
{
	UpdateCharacterCollision(this);
	UpdateAllCharacterAnimation(game, this);
	HandleCharacterProjectileFiring(this, game);
}
