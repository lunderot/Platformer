#include <limits>
#include <algorithm>

#include "math/Vec2.h"
#include "math/Box.h"

float SweptAABB(Box box1, Vec2f box1vel, Box box2, Vec2f box2vel, Vec2f& normal);