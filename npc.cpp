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

void NPC::UpdatePatrolRoute()
{

	int travelDistance = (PlayerSprite->BitSize * PlayerSprite->Scale) * 2;

	PlayerSprite->Movement.Speed = 1;
	PlayerSprite->Movement.LastState = PlayerSprite->Movement.CurrentState;
	PlayerSprite->Movement.LastDirection = PlayerSprite->Movement.CurrentDirection;

	if (PatrolRoute.Counter == 0)
	{
		
		PlayerSprite->Movement.CurrentDirection = PatrolRoute.Route[PatrolRoute.Currentindex];
		PlayerSprite->Movement.CurrentState = State::Walking;
		PlayerSprite->Movement.Velocity = DirectionToVelocity(PatrolRoute.Route[PatrolRoute.Currentindex]);
	}
	if ((PatrolRoute.LastPosition.x + travelDistance < PlayerSprite->Movement.Position.x ||
		PatrolRoute.LastPosition.y + travelDistance < PlayerSprite->Movement.Position.y ||
		PatrolRoute.LastPosition.x - travelDistance > PlayerSprite->Movement.Position.x ||
		PatrolRoute.LastPosition.y - travelDistance > PlayerSprite->Movement.Position.y )&&
		PatrolRoute.Counter == 0
		)
	{
		PlayerSprite->Movement.CurrentState = State::Idle;
		PlayerSprite->Movement.Velocity = { 0,0 };
		PatrolRoute.Counter++;
		PatrolRoute.Currentindex++;
		if (PatrolRoute.Currentindex >= PatrolRoute.Route.size())
		{
			PatrolRoute.Currentindex = 0;
		}
		// so im thinking check to see if theyre going the same direction again and dont make them stop if they are
	}
	if (PatrolRoute.Counter != 0)
	{
		PatrolRoute.Counter++;
	}
	if (PatrolRoute.Counter > PatrolRoute.WaitTick)
	{
		PatrolRoute.Counter = 0;
		PatrolRoute.LastPosition = PlayerSprite->Movement.Position;
	}
}

void NPC::UpdateNPC(Game* game)
{
	UpdatePatrolRoute();
	UpdateCharacterCollision(this);
	UpdateAllCharacterAnimation(game, this);
	HandleCharacterProjectileFiring(this, game);
}
