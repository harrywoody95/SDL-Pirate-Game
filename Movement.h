#pragma once
#include "Vec2.h"
#include <string>

enum Direction {
	North,
	East,
	South,
	West,
};
enum State {
	Idle,
	Walking,
	Running,
	Attack,
	Dig,
	Sailing,
	FullSailing,
	Dead,
};

struct Movement {

	static const int WalkingSpeed = 2;
	static const int RunningSpeed = 3;
	static const int AttackSpeed = 1;
	static const int SailSpeed = 2;
	static const int FullSailSpeed = 3;
	static const int ProjectileSpeed = 9;
	

	Vec2 Position = {0, 0};
	Vec2 Velocity = {0, 0};
	State LastState = Idle;
	State CurrentState = Idle;
	Direction LastDirection = East;
	Direction CurrentDirection = East;
	int Speed = WalkingSpeed;

	void init(float PosX, float PosY)
	{
		Position.x = PosX;
		Position.y = PosY;
		Velocity.x = 0.0;
		Velocity.y = 0.0;
	}
	void SetPosition(float PosX, float PosY)
	{
		Position.x = PosX;
		Position.y = PosY;
	}

	void Update()
	{
		Position.x = Position.x + (Velocity.x * Speed);
		Position.y = Position.y + (Velocity.y * Speed);
	}
	
	void GetSpeed()
	{
		// maybe a switch would do better here
		if (CurrentState == Walking)
		{

		}
		if (CurrentState == Running)
		{

		}
		if (CurrentState == Sailing)
		{

		}
		if (CurrentState == FullSailing)
		{

		}
	}
};

State StringToState(std::string state);
Direction StringToDirection(std::string direction);
