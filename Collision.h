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

bool IsPointInsideBox(Box box, Vec2 point);

bool BoxesOverlap(Box a, Box b);

#endif // COLLISION_H