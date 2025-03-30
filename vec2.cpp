#include "Vec2.h"

Vec2& Vec2::Add(Vec2 v)
{
	Vec2 vec;
	vec.x = this->x + v.x;
	vec.y = this->y + v.y;
	return vec;
}

Vec2& Vec2::Subtract(Vec2 v)
{
	Vec2 vec;
	vec.x = this->x - v.x;
	vec.y = this->y - v.y;
	return vec;
}

Vec2& Vec2::Multiply(Vec2 v)
{
	Vec2 vec;
	vec.x = this->x * v.x;
	vec.y = this->y * v.y;
	return vec;
}

Vec2& Vec2::Divide(Vec2 v)
{
	Vec2 vec;
	vec.x = this->x / v.x;
	vec.y = this->y / v.y;
	return vec;
}
