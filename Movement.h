#pragma once
#include "Vec2.h"
#include <string>

struct Entity;

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
	static const int ProjectileSpeed = 7;
	

	Vec2 Position = {0, 0};
	Vec2 Velocity = {0, 0};
	State LastState = Idle;
	State CurrentState = Idle;
	Direction LastDirection = East;
	Direction CurrentDirection = East;
	int Speed = WalkingSpeed;

	void init(Entity* e, float PosX, float PosY);

	void SetPosition(Entity* e, float PosX, float PosY);

	void Update(Entity* e);

	void SetSpeed(int speed);

};

State StringToState(std::string state);
Direction StringToDirection(std::string direction);
