#pragma once

#include <glm/glm.hpp>

struct AngularImpulse
{
	glm::vec2 force;
	glm::vec2 offset;
	glm::f32 time;

	AngularImpulse(glm::vec2 force, glm::vec2 offset, glm::f32 time)
	{
		this->force = force;
		this->offset = offset;
		this->time = time;
	}
};

