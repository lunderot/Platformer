#pragma once
#include "Entity.h"

#include <glm/gtc/matrix_transform.hpp>

class Camera : public Entity
{
private:
	glm::vec2 size;
	float scale;
public:
	Camera(glm::vec2 size, glm::vec2 position = glm::vec2(), float scale = 1.0f);
	~Camera();

	glm::vec2 GetSize();

	glm::mat4 GetCameraMatrix() const;
	float GetScale() const;
};

