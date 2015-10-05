#pragma once

#include <glm/glm.hpp>

struct Moment
{
	glm::vec2 force;
	glm::vec2 offset;

	Moment(glm::vec2 force, glm::vec2 offset)
	{
		this->force = force;
		this->offset = offset;
	}
};