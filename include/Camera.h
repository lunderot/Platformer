#pragma once
#include "Entity.h"
class Camera : public Entity
{
private:
	glm::vec2 size;
public:
	Camera(glm::vec2 size, glm::vec2 position = glm::vec2());
	~Camera();

	glm::vec2 GetSize();
};

