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
	if (Target != nullptr)
	{
		return;
	}

	int travelDistance = (PlayerSprite->BitSize * PlayerSprite->Scale) * 2;

	PlayerSprite->Movement.Speed = 1;
	PlayerSprite->Movement.LastState = PlayerSprite->Movement.CurrentState;
	PlayerSprite->Movement.LastDirection = PlayerSprite->Movement.CurrentDirection;
	if (PatrolRoute.Route.size() == 0 || Target != nullptr)
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

void NPC::UpdateHostile(Game* game)
{
	if (!Hostile)
	{
		return;
	}
	PlayerSprite->Movement.LastState = PlayerSprite->Movement.CurrentState;
	if (CurrentEquipment->Type != EquipmentType::Gun && CurrentEquipment->Type != EquipmentType::Sword)
	{
		return;
	}
	
	if (CurrentEquipment->Type == EquipmentType::Gun)
	{
		ScanforTarget(game, 500);
		if (LineOfSight(this->Target))
		{
			//dont move.. attack
			AttackTarget(this->Target);
			return;
		}

		if (HostileDirection != nullptr && game->PlayerEntity->Player.PlayerSprite->Movement.CurrentDirection == game->PlayerEntity->Player.PlayerSprite->Movement.LastDirection)
		{
			return;
		}

		Vec2* HostilePosition = &this->PlayerSprite->Movement.Position;
		Vec2* TargetPosition = &game->PlayerEntity->Player.PlayerSprite->Movement.Position;
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
		if (PlayerInRange(game, 40))
		{
			//dont move.. attack
			AttackTarget(Target);
		}

		if (HostileDirection == nullptr || game->PlayerEntity->Player.PlayerSprite->Movement.CurrentDirection != game->PlayerEntity->Player.PlayerSprite->Movement.LastDirection || !PlayerInRange(game, 20))
		{

			Vec2* HostilePosition = &this->PlayerSprite->Movement.Position;
			Vec2* TargetPosition = &game->PlayerEntity->Player.PlayerSprite->Movement.Position;

			int distanceX = abs(TargetPosition->x - HostilePosition->x);   
			int distanceY = abs(TargetPosition->y - HostilePosition->y);


			int threshold = 50;

			if (abs(distanceX - distanceY) < threshold)
			{

				if (!MoveBlocked)
				{
					PlayerSprite->Movement.Velocity = DirectionToVelocity(PlayerSprite->Movement.CurrentDirection);
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

	if (BoxCollision(this->Collision, CollisionBoxes, this->PlayerSprite->Movement.Speed, &this->PlayerSprite->Movement.CurrentDirection, this->PlayerSprite->Movement.Velocity, &OutVelocity))
	{
		this->PlayerSprite->Movement.Velocity = OutVelocity;
		if (this->PlayerSprite->Movement.CurrentState != Attack)
		{
			this->PlayerSprite->Movement.CurrentState = Idle;
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

	if (player->Player.PlayerSprite->Movement.Position.x > this->PlayerSprite->Movement.Position.x)
	{
		DistanceX = player->Player.PlayerSprite->Movement.Position.x - this->PlayerSprite->Movement.Position.x;
	}
	else
	{
		DistanceX = this->PlayerSprite->Movement.Position.x - player->Player.PlayerSprite->Movement.Position.x;
	}

	if (player->Player.PlayerSprite->Movement.Position.y > this->PlayerSprite->Movement.Position.y)
	{
		if(player->Player.PlayerSprite->Movement.Position.y - this->PlayerSprite->Movement.Position.y)
		{
			DistanceY = player->Player.PlayerSprite->Movement.Position.y - this->PlayerSprite->Movement.Position.y;
		}
	}
	else
	{
		DistanceY = this->PlayerSprite->Movement.Position.y - player->Player.PlayerSprite->Movement.Position.y;
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
		PlayerSprite->DeleteSprite(&game->SpriteList);
		CostumeSprite->DeleteSprite(&game->SpriteList);
		EquipmentSprite->DeleteSprite(&game->SpriteList);
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
	PlayerSprite->Movement.Speed = 0;
	PlayerSprite->Movement.CurrentState = Dead;
	UpdateAllCharacterAnimation(game, this);
	PlayerSprite->Movement.LastState = Dead;
	Collision = { 0,0,0,0 };
	DeadBodyDisappearCounter++;
	return;
}

bool NPC::LineOfSight(Character* Target)
{
	Vec2* HostilePosition = &this->PlayerSprite->Movement.Position;
	Vec2* TargetPosition = &Target->PlayerSprite->Movement.Position;
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
	Vec2* HostilePosition = &this->PlayerSprite->Movement.Position;
	Vec2* TargetPosition = &Target->PlayerSprite->Movement.Position;
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
			PlayerSprite->Movement.LastDirection = PlayerSprite->Movement.CurrentDirection;
			PlayerSprite->Movement.CurrentDirection = North;
		}
		else
		{
			PlayerSprite->Movement.LastDirection = PlayerSprite->Movement.CurrentDirection;
			PlayerSprite->Movement.CurrentDirection = South;
		}
	}
	else
	{
		if (HostilePosition->x > TargetPosition->x)
		{
			PlayerSprite->Movement.LastDirection = PlayerSprite->Movement.CurrentDirection;
			PlayerSprite->Movement.CurrentDirection = West;
		}
		else
		{
			PlayerSprite->Movement.LastDirection = PlayerSprite->Movement.CurrentDirection;
			PlayerSprite->Movement.CurrentDirection = East;
		}
	}
}

void NPC::AttackTarget(Character* Target)
{
	PlayerSprite->Movement.LastState = PlayerSprite->Movement.CurrentState;
	FaceTarget(Target);
	PlayerSprite->Movement.CurrentState = Attack;
	PlayerSprite->Movement.Velocity = { 0,0 };
	if (HostileDirection != nullptr)
	{
		delete HostileDirection;
		HostileDirection = nullptr;
	}
	return;
}

void NPC::MoveInDirection(Direction direction)
{
	PlayerSprite->Movement.CurrentDirection = direction;
	PlayerSprite->Movement.CurrentState = State::Walking;
	if (!MoveBlocked)
	{
		PlayerSprite->Movement.Velocity = DirectionToVelocity(PlayerSprite->Movement.CurrentDirection);
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
	PlayerSprite->Movement.Speed = speed;
	PlayerSprite->Movement.LastState = PlayerSprite->Movement.CurrentState;
	PlayerSprite->Movement.LastDirection = PlayerSprite->Movement.CurrentDirection;
}
