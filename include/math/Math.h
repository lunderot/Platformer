#include <limits>
#include <algorithm>
#include <stdexcept>

#include "math/Vec2.h"
#include "math/Box.h"

#include "math/Circle.h"
#include "math/LineSegment.h"

float SweptAABB(Box box1, Vec2f box1vel, Box box2, Vec2f box2vel, Vec2f& normal);

Vec2f ClosestPoint(LineSegment line, Circle circle);
Vec2f LineSegmentCircleCollision(LineSegment line, Circle circle);