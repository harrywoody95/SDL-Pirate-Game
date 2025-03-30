#include "Movement.h"
#include <string>

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
