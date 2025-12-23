#include "NPC.h"
#include "Game.h"
// **** should make these function not members of NPC and instead get a list of all NPC and do it for all of them.
Entity* CreateNPC(float x, float y, Game* game)
{
	Entity* entity = CreateEntity(x, y, game, EntityType::NPC);
	NPC* NPC = &entity->NPC;
	NPC->TransparentTexture = TextureManager::LoadTexture("Assets/Sprites/Character/transparent.png");
	NPC->Sprites.Body = new Sprite();
	NPC->Sprites.Body->CreateSprite(x, y, "Assets/Sprites/Character/transparent.png", 16, 4, &game->SpriteList);
	NPC->Sprites.Costume = new Sprite();
	NPC->Sprites.Costume->CreateSprite(x, y, "Assets/Sprites/Character/transparent.png", 16, 4, &game->SpriteList);
	NPC->Sprites.Equipment = new Sprite();
	NPC->Sprites.Equipment->CreateSprite(x, y, "Assets/Sprites/Character/transparent.png", 16, 4, &game->SpriteList);
	NPC->EffectSprite = new Sprite ();
	NPC->EffectSprite->CreateSprite(x, y, "Assets/Sprites/Character/transparent.png", 16, 4, &game->SpriteList);
	NPC->Sprites.Body->Name = "Sprites.Body";
	NPC->Sprites.Costume->Name = "Sprites.Costume";
	NPC->Sprites.Equipment->Name = "Sprites.Equipment";
	NPC->EffectSprite->Name = "EffectSprite";
	SetPlayerAnimation(game, entity);
	SetCostumeAnimation(game, entity);
	SetEquipmentAnimation(game, entity);
	return entity;
}

void UpdatePatrolRoute(Game* game, Entity* Patroller)
{
	NPC* Character = &Patroller->NPC;

		int travelDistance = (Character->Sprites.Body->BitSize * Character->Sprites.Body->Scale) * 2;
		int nextIndex;

		Patroller->Movement.SetSpeed(1);

		if (Character->PatrolRoute.Route.size() == 0 || Character->Target != nullptr)
		{
			return;
		}
		if (Character->PatrolRoute.Counter == 0)
		{

			Patroller->Movement.CurrentDirection = Character->PatrolRoute.Route[Character->PatrolRoute.Currentindex];
			Patroller->Movement.CurrentState = State::Walking;
			Patroller->Movement.Velocity = DirectionToVelocity(Character->PatrolRoute.Route[Character->PatrolRoute.Currentindex]);
			nextIndex = Character->PatrolRoute.Currentindex + 1;
			if (Character->PatrolRoute.Currentindex >= Character->PatrolRoute.Route.size() - 1)
			{
				nextIndex = 0;
			}
			if (Character->PatrolRoute.Route[Character->PatrolRoute.Currentindex] == Character->PatrolRoute.Route[nextIndex])
			{
				travelDistance = travelDistance * 2;
				Character->PatrolRoute.Currentindex = nextIndex;
			}
		}
		if ((Character->PatrolRoute.LastPosition.x + travelDistance < Patroller->Movement.Position.x ||
			Character->PatrolRoute.LastPosition.y + travelDistance < Patroller->Movement.Position.y ||
			Character->PatrolRoute.LastPosition.x - travelDistance > Patroller->Movement.Position.x ||
			Character->PatrolRoute.LastPosition.y - travelDistance > Patroller->Movement.Position.y) &&
			Character->PatrolRoute.Counter == 0
			)
		{
			Patroller->Movement.CurrentState = State::Idle;
			Patroller->Movement.Velocity = { 0,0 };
			Character->PatrolRoute.Counter++;
			Character->PatrolRoute.Currentindex++;
			if (Character->PatrolRoute.Currentindex >= Character->PatrolRoute.Route.size() - 1)
			{
				Character->PatrolRoute.Currentindex = 0;
			}
		}
		if (Character->PatrolRoute.Counter != 0)
		{
			Character->PatrolRoute.Counter++;
		}
		if (Character->PatrolRoute.Counter > Character->PatrolRoute.WaitTick)
		{
			Character->PatrolRoute.Counter = 0;
			Character->PatrolRoute.LastPosition = Patroller->Movement.Position;
		}
	
}

void UpdateHostile(Game* game, Entity* e)
{

		NPC* Character = &e->NPC;
		if (!Character->Hostile)
		{
			return;
		}
		e->Movement.LastState = e->Movement.CurrentState;
		if (Character->CurrentEquipment->Type != EquipmentType::Gun && Character->CurrentEquipment->Type != EquipmentType::Sword)
		{
			return;
		}

		if (Character->CurrentEquipment->Type == EquipmentType::Gun)
		{
			ScanforTarget(game, e, 500);
			if (Character->Target == nullptr)
			{
				return;
			}

			if (LineOfSight(Character->Target, e))
			{
				//dont move.. attack
				AttackTarget(Character->Target, e);
				return;
			}

			if (Character->HostileDirection != nullptr && game->PlayerEntity->Movement.CurrentDirection == game->PlayerEntity->Movement.LastDirection)
			{
				return;
			}

			Vec2* HostilePosition = &e->Movement.Position;
			Vec2* TargetPosition = &game->PlayerEntity->Movement.Position;
			int distanceX = abs(TargetPosition->x - HostilePosition->x);
			int distanceY = abs(TargetPosition->y - HostilePosition->y);

			if (distanceY > distanceX)
			{
				e->Movement.SetSpeed(1);
				if (HostilePosition->y > TargetPosition->y)
				{
					NPCMoveInDirection(North, e);
					return;
				}
				else
				{
					NPCMoveInDirection(South, e);
					return;
				}
			}
			else
			{
				e->Movement.SetSpeed(1);
				if (HostilePosition->x > TargetPosition->x)
				{
					NPCMoveInDirection(West, e);
					return;
				}
				else
				{
					NPCMoveInDirection(East, e);
					return;
				}
			}
		}

		if (Character->CurrentEquipment->Type == EquipmentType::Sword)
		{
			ScanforTarget(game, e, 500);
			if (Character->Target == nullptr)
			{
				return;
			}
			if (PlayerInRange(game, e, 40))
			{
				//dont move.. attack
				AttackTarget(Character->Target, e);
			}

			if (Character->HostileDirection == nullptr || game->PlayerEntity->Movement.CurrentDirection != game->PlayerEntity->Movement.LastDirection || !PlayerInRange(game, e, 20))
			{

				Vec2* HostilePosition = &e->Movement.Position;
				Vec2* TargetPosition = &game->PlayerEntity->Movement.Position;

				int distanceX = abs(TargetPosition->x - HostilePosition->x);
				int distanceY = abs(TargetPosition->y - HostilePosition->y);


				int threshold = 50;

				if (abs(distanceX - distanceY) < threshold)
				{

					if (!Character->MoveBlocked)
					{
						e->Movement.Velocity = DirectionToVelocity(e->Movement.CurrentDirection);
					}
					return;
				}

				if (distanceY > distanceX)
				{
					e->Movement.SetSpeed(2);

					if (HostilePosition->y > TargetPosition->y)
					{
						NPCMoveInDirection(North, e);
						return;
					}
					else
					{
						NPCMoveInDirection(South, e);
						return;
					}
				}
				else
				{
					e->Movement.SetSpeed(2);

					if (HostilePosition->x > TargetPosition->x)
					{
						NPCMoveInDirection(West, e);
						return;
					}
					else
					{
						NPCMoveInDirection(East, e);
						return;
					}
				}
			}
		}
	
}

void NPC::UpdateNPC(Game* game, Entity* NPC)
{
	if (Health <= 0)
	{
		Die(game, NPC);
		return;
	}
	if (BeenAttacked)
	{
		Hostile = true;
	}
	if (!CanAttack)
	{
		AttackCooldown++;
	}
	UpdatePatrolRoute(game, NPC);
	UpdateCharacterCollision(NPC);
	UpdateCharacterHitbox(this);
	NPCBoxCollision(game, NPC);
	UpdateHostile(game, NPC);
	UpdateAllCharacterAnimation(game, NPC);
	HandleCharacterProjectileFiring(NPC, game);
}

void NPCBoxCollision(Game* Game, Entity* e)
{
	std::vector <Box> CollisionBoxes;
	NPC* character = &e->NPC;

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
		if (character != &list[x]->NPC)
		{
			CollisionBoxes.push_back(list[x]->NPC.Collision);
		}
	}
	CollisionBoxes.push_back(Game->PlayerEntity->Player.Collision);

	Vec2 OutVelocity = { 0.0, 0.0 };

	if (BoxCollision(character->Collision, CollisionBoxes, e->Movement.Speed, &e->Movement.CurrentDirection, e->Movement.Velocity, &OutVelocity))
	{
		e->Movement.Velocity = OutVelocity;
		if (e->Movement.CurrentState != Attack)
		{
			e->Movement.CurrentState = Idle;
		}
		character->MoveBlocked = true;
	}
	else
	{
		character->MoveBlocked = false;
	}

}

bool PlayerInRange(Game* game, Entity* SearchingEntity, int Tolerence)
{
	Entity* player = game->PlayerEntity;
	
	int DistanceX = 0;
	int DistanceY = 0;

	if (player->Movement.Position.x > SearchingEntity->Movement.Position.x)
	{
		DistanceX = player->Movement.Position.x - SearchingEntity->Movement.Position.x;
	}
	else
	{
		DistanceX = SearchingEntity->Movement.Position.x - player->Movement.Position.x;
	}

	if (player->Movement.Position.y > SearchingEntity->Movement.Position.y)
	{
		if(player->Movement.Position.y - SearchingEntity->Movement.Position.y)
		{
			DistanceY = player->Movement.Position.y - SearchingEntity->Movement.Position.y;
		}
	}
	else
	{
		DistanceY = SearchingEntity->Movement.Position.y - player->Movement.Position.y;
	}

	if (DistanceX < 0)
	{
		DistanceX = DistanceX * -1;
	}

	if (DistanceY < 0)
	{
		DistanceY = DistanceY * -1;
	}

	if (DistanceX <= Tolerence && DistanceY <= Tolerence)
	{
		return true;
	}

	return false;
}

void Die(Game* game, Entity* e)
{
	NPC* character = &e->NPC;
	if (character->DeadBodyDisappearCounter > 2000)
	{
		character->Sprites.Body->DeleteSprite(&game->SpriteList);
		character->Sprites.Costume->DeleteSprite(&game->SpriteList);
		character->Sprites.Equipment->DeleteSprite(&game->SpriteList);
		character->EffectSprite->DeleteSprite(&game->SpriteList);
		for (int x = 0; x < game->EntityList.size(); x++)
		{
			if (&game->EntityList[x]->NPC == character)
			{
				DestroyEntity(game, game->EntityList[x]);
				return;
			}
		}
	}
	e->Movement.Speed = 0;
	e->Movement.CurrentState = Dead;
	UpdateAllCharacterAnimation(game, e);
	e->Movement.LastState = Dead;
	character->Collision = { 0,0,0,0 };
	character->DeadBodyDisappearCounter++;
	return;
}

bool LineOfSight(Entity* Target, Entity* Attacker)
{
	Vec2* HostilePosition = &Attacker->Movement.Position;
	Vec2* TargetPosition = &Target->Movement.Position;
	int distanceX = 0;
	int distanceY = 0;

	if (HostilePosition->x > TargetPosition->x)
	{
		distanceX = HostilePosition->x - TargetPosition->x;
		if (distanceX < 0)
		{
			distanceX = distanceX * -1;
		}
	}
	else
	{
		distanceX = TargetPosition->x - HostilePosition->x;
		if (distanceX < 0)
		{
			distanceX = distanceX * -1;
		}
	}
	if (HostilePosition->y > TargetPosition->y)
	{
		distanceY = HostilePosition->y - TargetPosition->y;
		if (distanceY < 0)
		{
			distanceY = distanceY * -1;
		}
	}
	else
	{
		distanceY = TargetPosition->y - HostilePosition->y;
		if (distanceY < 0)
		{
			distanceY = distanceY * -1;
		}
	}

	if (distanceX <= 15 || distanceY <= 15)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void FaceTarget(Entity* Target, Entity* Attacker)
{
	Vec2* HostilePosition = &Attacker->Movement.Position;
	Vec2* TargetPosition = &Target->Movement.Position;
	int distanceX = 0;
	int distanceY = 0;

	if (HostilePosition->x > TargetPosition->x)
	{
		distanceX = HostilePosition->x - TargetPosition->x;
		if (distanceX < 0)
		{
			distanceX = distanceX * -1;
		}
	}
	else
	{
		distanceX = TargetPosition->x - HostilePosition->x;
		if (distanceX < 0)
		{
			distanceX = distanceX * -1;
		}
	}
	if (HostilePosition->y > TargetPosition->y)
	{
		distanceY = HostilePosition->y - TargetPosition->y;
		if (distanceY < 0)
		{
			distanceY = distanceY * -1;
		}
	}
	else
	{
		distanceY = TargetPosition->y - HostilePosition->y;
		if (distanceY < 0)
		{
			distanceY = distanceY * -1;
		}
	}
	if (distanceX <= 15)
	{
		if (HostilePosition->y > TargetPosition->y)
		{
			Attacker->Movement.LastDirection = Attacker->Movement.CurrentDirection;
			Attacker->Movement.CurrentDirection = North;
		}
		else
		{
			Attacker->Movement.LastDirection = Attacker->Movement.CurrentDirection;
			Attacker->Movement.CurrentDirection = South;
		}
	}
	else
	{
		if (HostilePosition->x > TargetPosition->x)
		{
			Attacker->Movement.LastDirection = Attacker->Movement.CurrentDirection;
			Attacker->Movement.CurrentDirection = West;
		}
		else
		{
			Attacker->Movement.LastDirection = Attacker->Movement.CurrentDirection;
			Attacker->Movement.CurrentDirection = East;
		}
	}
}

void AttackTarget(Entity* Target, Entity* Attacker)
{
	Attacker->Movement.LastState = Attacker->Movement.CurrentState;
	FaceTarget(Target, Attacker);
	Attacker->Movement.CurrentState = Attack;
	Attacker->Movement.Velocity = { 0,0 };
	if (Attacker->NPC.HostileDirection != nullptr)
	{
		delete Attacker->NPC.HostileDirection;
		Attacker->NPC.HostileDirection = nullptr;
	}
	return;
}

void NPCMoveInDirection(Direction direction, Entity* e)
{
	e->Movement.CurrentDirection = direction;
	e->Movement.CurrentState = State::Walking;
	if (!e->NPC.MoveBlocked)
	{
		e->Movement.Velocity = DirectionToVelocity(e->Movement.CurrentDirection);
	}
	if (e->NPC.HostileDirection != nullptr)
	{
		delete e->NPC.HostileDirection;
		e->NPC.HostileDirection = nullptr;
	}
	if (e->NPC.Hostile)
	{
		Direction* d = new Direction(direction);
		e->NPC.HostileDirection = d;
	}
	// if move blocked find a path around
	return;
}

bool ScanforTarget(Game* game, Entity* Scanner, int range)
{
	if (PlayerInRange(game, Scanner, range) && Scanner->NPC.Target == nullptr)
	{
		Scanner->NPC.Target = game->PlayerEntity;
		return true;
	}
	if (!PlayerInRange(game, Scanner, range))
	{
		Scanner->NPC.Target = nullptr;
		return false;
	}
	if (Scanner->NPC.Target == nullptr)
	{
		return false;
	}
}

