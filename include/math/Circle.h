#pragma once

#include <glm/glm.hpp>

class Circle
{
public:
	glm::vec2 position;
	float radius;
public:
	Circle(glm::vec2 position, float radius);
	~Circle();
};

