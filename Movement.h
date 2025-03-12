#pragma once
#include "Vec2.h"

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
};

struct Movement {
	Vec2 Position;
	Vec2 Velocity;
	State LastState;
	State CurrentState = Idle;
	Direction LastDirection;
	Direction CurrentDirection = East;
	int Speed = 3;

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
};
