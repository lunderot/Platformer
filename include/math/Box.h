#pragma once

#include "math/Vec2.h"

class Box
{
public:
	Vec2f position;
	Vec2f size;
public:
	Box(Vec2f position, Vec2f size);
	~Box();
};

