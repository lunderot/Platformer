#pragma once

#include "Body.h"

class CircleBody : public Body
{
private:
	glm::f32 radius;
public:
	CircleBody(glm::vec2 position, glm::f32 mass, glm::f32 radius);
	~CircleBody();

	glm::f32 GetInertia() const;
};

