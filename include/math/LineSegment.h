#pragma once

#include "math/Vec2.h"

class LineSegment
{
public:
	Vec2f point[2];
public:
	LineSegment(Vec2f point1, Vec2f point2);
	~LineSegment();
};

