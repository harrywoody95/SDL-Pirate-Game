#pragma once
struct Vec2 {

	float x;
	float y;

	Vec2& Add(Vec2 v);
	Vec2& Subtract(Vec2 v);
	Vec2& Multiply(Vec2 v);
	Vec2& Divide(Vec2 v);
	
};
struct Vec2i {
	int x;
	int y;
};