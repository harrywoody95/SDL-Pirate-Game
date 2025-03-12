#pragma once
#include "Vec2.h"

struct Player;

struct Camera {
	Vec2i Position;
	Vec2i Size;
};

void UpdateCamera(Camera* camera, Player* player); 
