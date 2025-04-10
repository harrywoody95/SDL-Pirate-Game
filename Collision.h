#pragma once
#ifndef COLLISION_H
#define COLLISION_H
#include "Vec2.h"

struct Box {
	float Left;
	float Right;
	float Top;
	float Bottom;
};

//the bigger the scale value, the smaller the box. not sure how to flip that - research
const static Box CharacterCollisionBoxScale = { 0.25f, 0.25f, 0.3f, 0.3f };
const static Box BulletHitBoxScale = { 0.4f, 0.4f, 0.4f, 0.4f };

bool IsPointInsideBox(Box box, Vec2 point);

bool BoxesOverlap(Box a, Box b);

#endif // COLLISION_H