#include "Movement.h"
#include <string>
#include "Entity.h"

std::string StateToString(State state)
{
	if (state == State::Idle)
	{
		return "Idle";
	}
	if (state == State::Walking)
	{
		return "Walk";
	}
	if (state == State::Running)
	{
		return "Run";
	}
	if (state == State::Sailing)
	{
		return "Sailing";
	}
	if (state == State::FullSailing)
	{
		return "FullSailing";
	}
	if (state == State::Dead)
	{
		return "Die";
	}
	if (state == State::Attack)
	{
		return "Attack";
	}
	if (state == State::Dig)
	{
		return "Dig";
	}
}

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

std::string DirectionToString(Direction direction)
{
	if (direction == Direction::South)
	{
		return "Down";
	}
	if (direction == Direction::North)
	{
		return "Up";
	}
	if (direction == Direction::West)
	{
		return "Left";
	}
	if (direction == Direction::East)
	{
		return "Right";
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