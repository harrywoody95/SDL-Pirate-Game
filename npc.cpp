#include "NPC.h"
#include "Game.h"

Entity* CreateNPC(float x, float y, Game* game)
{
	Entity* entity = CreateEntity(x, y, game, EntityType::NPC);
	NPC* NPC = &entity->NPC;
	NPC->Sprites.Body = new Sprite();
	NPC->Sprites.Body->CreateSprite(x, y, "Assets/Sprites/Character/transparent.png", 16, 4, &game->SpriteList);
	NPC->Sprites.Costume = new Sprite();
	NPC->Sprites.Costume->CreateSprite(x, y, "Assets/Sprites/Character/transparent.png", 16, 4, &game->SpriteList);
	NPC->Sprites.Equipment = new Sprite();
	NPC->Sprites.Equipment->CreateSprite(x, y, "Assets/Sprites/Character/transparent.png", 16, 4, &game->SpriteList);
	NPC->EffectSprite = new Sprite();
	NPC->EffectSprite->CreateSprite(x, y, "Assets/Sprites/Character/transparent.png", 16, 4, &game->SpriteList);
	NPC->Sprites.Body->Name = "Sprites.Body";
	NPC->Sprites.Costume->Name = "Sprites.Costume";
	NPC->Sprites.Equipment->Name = "Sprites.Equipment";
	NPC->EffectSprite->Name = "EffectSprite";
	SetPlayerAnimation(game, NPC);
	SetCostumeAnimation(game, NPC);
	SetEquipmentAnimation(game, NPC);
	return entity;
}

void NPC::UpdatePatrolRoute()
{
	if (Target != nullptr)
	{
		return;
	}

	int travelDistance = (Sprites.Body->BitSize * Sprites.Body->Scale) * 2;
	int nextIndex;

	SetSpeed(1);
	if (PatrolRoute.Route.size() == 0 || Target != nullptr)
	{
		return;
	}
	if (PatrolRoute.Counter == 0)
	{
		
		Sprites.Body->Movement.CurrentDirection = PatrolRoute.Route[PatrolRoute.Currentindex];
		Sprites.Body->Movement.CurrentState = State::Walking;
		Sprites.Body->Movement.Velocity = DirectionToVelocity(PatrolRoute.Route[PatrolRoute.Currentindex]);
		nextIndex = PatrolRoute.Currentindex + 1;
		if (PatrolRoute.Currentindex >= PatrolRoute.Route.size() - 1)
		{
			nextIndex = 0;
		}
		if (PatrolRoute.Route[PatrolRoute.Currentindex] == PatrolRoute.Route[nextIndex])
		{
			travelDistance = travelDistance * 2;
			PatrolRoute.Currentindex = nextIndex;
		}
	}
	if ((PatrolRoute.LastPosition.x + travelDistance < Sprites.Body->Movement.Position.x ||
		PatrolRoute.LastPosition.y + travelDistance < Sprites.Body->Movement.Position.y ||
		PatrolRoute.LastPosition.x - travelDistance > Sprites.Body->Movement.Position.x ||
		PatrolRoute.LastPosition.y - travelDistance > Sprites.Body->Movement.Position.y )&&
		PatrolRoute.Counter == 0
		)
	{
		Sprites.Body->Movement.CurrentState = State::Idle;
		Sprites.Body->Movement.Velocity = { 0,0 };
		PatrolRoute.Counter++;
		PatrolRoute.Currentindex++;
		if (PatrolRoute.Currentindex >= PatrolRoute.Route.size() - 1)
		{
			PatrolRoute.Currentindex = 0;
		}
	}
	if (PatrolRoute.Counter != 0)
	{
		PatrolRoute.Counter++;
	}
	if (PatrolRoute.Counter > PatrolRoute.WaitTick)
	{
		PatrolRoute.Counter = 0;
		PatrolRoute.LastPosition = Sprites.Body->Movement.Position;
	}
}

void NPC::UpdateHostile(Game* game)
{
	if (!Hostile)
	{
		return;
	}
	Sprites.Body->Movement.LastState = Sprites.Body->Movement.CurrentState;
	if (CurrentEquipment->Type != EquipmentType::Gun && CurrentEquipment->Type != EquipmentType::Sword)
	{
		return;
	}
	
	if (CurrentEquipment->Type == EquipmentType::Gun)
	{
		ScanforTarget(game, 500);
		if(Target == nullptr)
		{
			return;
		}

		if (LineOfSight(this->Target))
		{
			//dont move.. attack
			AttackTarget(this->Target);
			return;
		}

		if (HostileDirection != nullptr && game->PlayerEntity->Player.Sprites.Body->Movement.CurrentDirection == game->PlayerEntity->Player.Sprites.Body->Movement.LastDirection)
		{
			return;
		}

		Vec2* HostilePosition = &this->Sprites.Body->Movement.Position;
		Vec2* TargetPosition = &game->PlayerEntity->Player.Sprites.Body->Movement.Position;
		int distanceX = abs(TargetPosition->x - HostilePosition->x);
		int distanceY = abs(TargetPosition->y - HostilePosition->y);

		if (distanceY > distanceX)
		{
			SetSpeed(1);
			if (HostilePosition->y > TargetPosition->y)
			{
				MoveInDirection(North);
				return;
			}
			else
			{
				MoveInDirection(South);
				return;
			}
		}
		else
		{
			SetSpeed(1);
			if (HostilePosition->x > TargetPosition->x)
			{
				MoveInDirection(West);
				return;
			}
			else
			{
				MoveInDirection(East);
				return;
			}
		}
	}

	if (CurrentEquipment->Type == EquipmentType::Sword)
	{
		ScanforTarget(game, 500);
		if (Target == nullptr)
		{
			return;
		}
		if (PlayerInRange(game, 40))
		{
			//dont move.. attack
			AttackTarget(Target);
		}

		if (HostileDirection == nullptr || game->PlayerEntity->Player.Sprites.Body->Movement.CurrentDirection != game->PlayerEntity->Player.Sprites.Body->Movement.LastDirection || !PlayerInRange(game, 20))
		{

			Vec2* HostilePosition = &this->Sprites.Body->Movement.Position;
			Vec2* TargetPosition = &game->PlayerEntity->Player.Sprites.Body->Movement.Position;

			int distanceX = abs(TargetPosition->x - HostilePosition->x);   
			int distanceY = abs(TargetPosition->y - HostilePosition->y);


			int threshold = 50;

			if (abs(distanceX - distanceY) < threshold)
			{

				if (!MoveBlocked)
				{
					Sprites.Body->Movement.Velocity = DirectionToVelocity(Sprites.Body->Movement.CurrentDirection);
				}
				return;
			}

			if (distanceY > distanceX)
			{
				SetSpeed(2);

				if (HostilePosition->y > TargetPosition->y)
				{
					MoveInDirection(North);
					return;
				}
				else
				{
					MoveInDirection(South);
					return;
				}
			}
			else
			{
				SetSpeed(2);

				if (HostilePosition->x > TargetPosition->x)
				{
					MoveInDirection(West);
					return;
				}
				else
				{
					MoveInDirection(East);
					return;
				}
			}
		}
	}
}

void NPC::UpdateNPC(Game* game)
{
	if (Health <= 0)
	{
		Die(game);
		return;
	}
	if (BeenAttacked)
	{
		Hostile = true;
	}
	UpdatePatrolRoute();
	UpdateCharacterCollision(this);
	UpdateCharacterHitbox(this);
	NPCBoxCollision(game);
	UpdateAllCharacterAnimation(game, this);
	UpdateHostile(game);
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

	if (BoxCollision(this->Collision, CollisionBoxes, this->Sprites.Body->Movement.Speed, &this->Sprites.Body->Movement.CurrentDirection, this->Sprites.Body->Movement.Velocity, &OutVelocity))
	{
		this->Sprites.Body->Movement.Velocity = OutVelocity;
		if (this->Sprites.Body->Movement.CurrentState != Attack)
		{
			this->Sprites.Body->Movement.CurrentState = Idle;
		}
		MoveBlocked = true;
	}
	else
	{
		MoveBlocked = false;
	}

}

bool NPC::PlayerInRange(Game* game, int Tolerence)
{
	Entity* player = game->PlayerEntity;
	
	int DistanceX = 0;
	int DistanceY = 0;

	if (player->Player.Sprites.Body->Movement.Position.x > this->Sprites.Body->Movement.Position.x)
	{
		DistanceX = player->Player.Sprites.Body->Movement.Position.x - this->Sprites.Body->Movement.Position.x;
	}
	else
	{
		DistanceX = this->Sprites.Body->Movement.Position.x - player->Player.Sprites.Body->Movement.Position.x;
	}

	if (player->Player.Sprites.Body->Movement.Position.y > this->Sprites.Body->Movement.Position.y)
	{
		if(player->Player.Sprites.Body->Movement.Position.y - this->Sprites.Body->Movement.Position.y)
		{
			DistanceY = player->Player.Sprites.Body->Movement.Position.y - this->Sprites.Body->Movement.Position.y;
		}
	}
	else
	{
		DistanceY = this->Sprites.Body->Movement.Position.y - player->Player.Sprites.Body->Movement.Position.y;
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

void NPC::Die(Game* game)
{
	if (DeadBodyDisappearCounter > 2000)
	{
		Sprites.Body->DeleteSprite(&game->SpriteList);
		Sprites.Costume->DeleteSprite(&game->SpriteList);
		Sprites.Equipment->DeleteSprite(&game->SpriteList);
		EffectSprite->DeleteSprite(&game->SpriteList);
		for (int x = 0; x < game->EntityList.size(); x++)
		{
			if (&game->EntityList[x]->NPC == this)
			{
				DestroyEntity(game, game->EntityList[x]);
				return;
			}
		}
	}
	Sprites.Body->Movement.Speed = 0;
	Sprites.Body->Movement.CurrentState = Dead;
	UpdateAllCharacterAnimation(game, this);
	Sprites.Body->Movement.LastState = Dead;
	Collision = { 0,0,0,0 };
	DeadBodyDisappearCounter++;
	return;
}

bool NPC::LineOfSight(Character* Target)
{
	Vec2* HostilePosition = &this->Sprites.Body->Movement.Position;
	Vec2* TargetPosition = &Target->Sprites.Body->Movement.Position;
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

void NPC::FaceTarget(Character* Target)
{
	Vec2* HostilePosition = &this->Sprites.Body->Movement.Position;
	Vec2* TargetPosition = &Target->Sprites.Body->Movement.Position;
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
			Sprites.Body->Movement.LastDirection = Sprites.Body->Movement.CurrentDirection;
			Sprites.Body->Movement.CurrentDirection = North;
		}
		else
		{
			Sprites.Body->Movement.LastDirection = Sprites.Body->Movement.CurrentDirection;
			Sprites.Body->Movement.CurrentDirection = South;
		}
	}
	else
	{
		if (HostilePosition->x > TargetPosition->x)
		{
			Sprites.Body->Movement.LastDirection = Sprites.Body->Movement.CurrentDirection;
			Sprites.Body->Movement.CurrentDirection = West;
		}
		else
		{
			Sprites.Body->Movement.LastDirection = Sprites.Body->Movement.CurrentDirection;
			Sprites.Body->Movement.CurrentDirection = East;
		}
	}
}

void NPC::AttackTarget(Character* Target)
{
	Sprites.Body->Movement.LastState = Sprites.Body->Movement.CurrentState;
	FaceTarget(Target);
	Sprites.Body->Movement.CurrentState = Attack;
	Sprites.Body->Movement.Velocity = { 0,0 };
	if (HostileDirection != nullptr)
	{
		delete HostileDirection;
		HostileDirection = nullptr;
	}
	return;
}

void NPC::MoveInDirection(Direction direction)
{
	Sprites.Body->Movement.CurrentDirection = direction;
	Sprites.Body->Movement.CurrentState = State::Walking;
	if (!MoveBlocked)
	{
		Sprites.Body->Movement.Velocity = DirectionToVelocity(Sprites.Body->Movement.CurrentDirection);
	}
	if (HostileDirection != nullptr)
	{
		delete HostileDirection;
		HostileDirection = nullptr;
	}
	if (Hostile)
	{
		Direction* d = new Direction(direction);
		HostileDirection = d;
	}
	// if move blocked find a path around
	return;
}

bool NPC::ScanforTarget(Game* game, int range)
{
	if (PlayerInRange(game, range) && Target == nullptr)
	{
		Target = &game->PlayerEntity->Player;
		return true;
	}
	if (!PlayerInRange(game, range))
	{
		Target = nullptr;
		return false;
	}
	if (Target == nullptr)
	{
		return false;
	}
}

void NPC::SetSpeed(int speed)
{
	Sprites.Body->Movement.Speed = speed;
	Sprites.Body->Movement.LastState = Sprites.Body->Movement.CurrentState;
	Sprites.Body->Movement.LastDirection = Sprites.Body->Movement.CurrentDirection;
}
