#pragma once

#include "Body.h"

class LineBody : public Body
{
private:
	glm::f32 length;
public:
	LineBody(glm::vec2 position, glm::f32 mass, glm::f32 length);
	~LineBody();

	glm::f32 GetInertia() const;

	glm::f32 GetLength() const;
};

