#pragma once

#include "math/Vec2.h"

class Circle
{
public:
	Vec2f position;
	float radius;
public:
	Circle(Vec2f position, float radius);
	~Circle();
};

