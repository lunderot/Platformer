#pragma once

#include <glm/glm.hpp>

struct Impulse
{
	glm::vec2 force;
	glm::f32 time;

	Impulse(glm::vec2 force, glm::f32 time)
	{
		this->force = force;
		this->time = time;
	}
};

