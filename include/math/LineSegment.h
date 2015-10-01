#pragma once

#include <glm/glm.hpp>

class LineSegment
{
public:
	glm::vec2 point[2];
public:
	LineSegment(glm::vec2 point1, glm::vec2 point2);
	~LineSegment();
};

