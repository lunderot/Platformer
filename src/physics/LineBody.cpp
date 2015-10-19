#include "physics/LineBody.h"


LineBody::LineBody(glm::vec2 position, glm::f32 mass, glm::f32 length) : Body(position, mass)
{
	this->length = length;
}


LineBody::~LineBody()
{
}

glm::f32 LineBody::GetInertia() const
{
	return (1 / 3.0f) * mass * length * length;
}

glm::f32 LineBody::GetLength() const
{
	return length;
}
