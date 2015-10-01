#pragma once

#include <glm/glm.hpp>

class Box
{
public:
	glm::vec2 position;
	glm::vec2 size;
public:
	Box(glm::vec2 position, glm::vec2 size);
	~Box();
};

