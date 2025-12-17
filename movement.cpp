#include "Movement.h"
#include <string>
#include "Entity.h"

State StringToState(std::string state)
{
	if (state == "Idle")
	{
		return State::Idle;
	}
	if (state == "Walk")
	{
		return State::Walking;
	}
	if (state == "Run")
	{
		return State::Running;
	}
	if (state == "Sailing")
	{
		return State::Sailing;
	}
	if (state == "FullSailing")
	{
		return State::FullSailing;
	}
	if (state == "Die")
	{
		return State::Dead;
	}
	if (state == "Attack")
	{
		return State::Attack;
	}
	if (state == "Dig")
	{
		return State::Dig;
	}
}

Direction StringToDirection(std::string direction)
{
	if (direction == "Down")
	{
		return Direction::South;
	}
	if (direction == "Up")
	{
		return Direction::North;
	}
	if (direction == "Left")
	{
		return Direction::West;
	}
	if (direction == "Right")
	{
		return Direction::East;
	}
}

void Movement::init(Entity* e, float PosX, float PosY)
{
	e->Movement.Position.x = PosX;
	e->Movement.Position.y = PosY;
	Velocity.x = 0.0;
	Velocity.y = 0.0;
}
void Movement::SetPosition(Entity* e, float PosX, float PosY)
{
	e->Movement.Position.x = PosX;
	e->Movement.Position.y = PosY;
}

void Movement::Update(Entity* e)
{
	e->Movement.Position.x = e->Movement.Position.x + (e->Movement.Velocity.x * Speed);
	e->Movement.Position.y = e->Movement.Position.y + (e->Movement.Velocity.y * Speed);
}

void Movement::SetSpeed(int speed)
{
	Speed = speed;
	LastState = CurrentState;
	LastDirection = CurrentDirection;
}