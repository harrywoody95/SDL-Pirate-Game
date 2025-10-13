#include "NPC.h"
#include "Game.h"

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

void NPC::UpdatePatrolRoute()
{

	int travelDistance = (PlayerSprite->BitSize * PlayerSprite->Scale) * 2;

	PlayerSprite->Movement.Speed = 1;
	PlayerSprite->Movement.LastState = PlayerSprite->Movement.CurrentState;
	PlayerSprite->Movement.LastDirection = PlayerSprite->Movement.CurrentDirection;
	if (PatrolRoute.Route.size() == 0 || Hostile)
	{
		return;
	}
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

void NPC::UpdateHostile()
{
	if (!Hostile)
	{
		return;
	}

	if (CurrentEquipment->Type != EquipmentType::Gun || CurrentEquipment->Type != EquipmentType::Sword)
	{
		return;
	}
	
	if (CurrentEquipment->Type == EquipmentType::Gun)
	{
		// if no line of sight find next move to have line of sight and move
		//if line of sight attack
		// EXAMPLE - Using player direction to decide, for example if its above and the enemy is below walking east, the character could shoot gun from two blocks ahead of the player downwards so the player will walk into them)
	}

	if (CurrentEquipment->Type == EquipmentType::Sword)
	{
		if (Target == nullptr)
		{
			//TARGET IS PLAYER/PLAYERS CREW
			//is a target in range
			//set target

			//no target in range clear target
		}
		// Find next move to player and move
		// if in range attack
	}
}

void NPC::UpdateNPC(Game* game)
{
	if (Health <= 0)
	{
		//death animation
		return;
	}
	UpdatePatrolRoute();
	UpdateCharacterCollision(this);
	UpdateCharacterHitbox(this);
	NPCBoxCollision(game);
	UpdateAllCharacterAnimation(game, this);
	HandleCharacterProjectileFiring(this, game);
}

void NPC::NPCBoxCollision(Game* Game)
{
	std::vector <Box> CollisionBoxes;

	for (int x = 0; x < Game->Map.LayerOne.size(); x++)
	{
		if (Game->Map.LayerOne[x].Solid)
		{
			CollisionBoxes.push_back(Game->Map.LayerOne[x].Collision);
		}
	}
	for (int x = 0; x < Game->Map.LayerTwo.size(); x++)
	{
		if (Game->Map.LayerTwo[x].Solid)
		{
			CollisionBoxes.push_back(Game->Map.LayerTwo[x].Collision);
		}
	}
	for (int x = 0; x < Game->Map.LayerThree.size(); x++)
	{
		if (Game->Map.LayerThree[x].Solid)
		{
			CollisionBoxes.push_back(Game->Map.LayerThree[x].Collision);
		}
	}
	std::vector <Entity*> list = GetEntitites(Game, EntityType::NPC);
	for (int x = 0; x < list.size(); x++)
	{
		if (this != &list[x]->NPC)
		{
			CollisionBoxes.push_back(list[x]->NPC.Collision);
		}
	}
	CollisionBoxes.push_back(Game->PlayerEntity->Player.Collision);

	Vec2 OutVelocity = { 0.0, 0.0 };

	if (BoxCollision(this->Collision, CollisionBoxes, this->PlayerSprite->Movement.Speed, &this->PlayerSprite->Movement.CurrentDirection, this->PlayerSprite->Movement.Velocity, &OutVelocity))
	{
		this->PlayerSprite->Movement.Velocity = OutVelocity;
		this->PlayerSprite->Movement.CurrentState = Idle;
	}
}
