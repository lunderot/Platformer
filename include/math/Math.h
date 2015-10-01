#include <limits>
#include <algorithm>
#include <stdexcept>

#include <glm/glm.hpp>
#include "math/Box.h"

#include "math/Circle.h"
#include "math/LineSegment.h"

float SweptAABB(Box box1, glm::vec2 box1vel, Box box2, glm::vec2 box2vel, glm::vec2& normal);

glm::vec2 ClosestPoint(LineSegment line, Circle circle);
glm::vec2 LineSegmentCircleCollision(LineSegment line, Circle circle);