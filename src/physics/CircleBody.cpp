#include "physics/CircleBody.h"


CircleBody::CircleBody(glm::vec2 position, glm::f32 mass, glm::f32 radius) : Body(position, mass)
{
	this->radius = radius;
}


CircleBody::~CircleBody()
{
}

glm::f32 CircleBody::GetInertia() const
{
	return (2.0f * mass * radius * radius) / 5.0f;
}