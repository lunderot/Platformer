#include "Camera.h"


Camera::Camera(glm::vec2 size, glm::vec2 position, float scale) : Entity(nullptr, 0, position)
{
	this->size = size;
	this->scale = scale;
}


Camera::~Camera()
{
}

glm::vec2 Camera::GetSize()
{
	return size;
}

glm::mat4 Camera::GetCameraMatrix() const
{
	glm::mat4 result = glm::inverse(glm::translate(glm::mat4(), glm::vec3(position * scale - size * 0.5f, 0)));
	return glm::scale(result, glm::vec3(scale, scale, scale));
}

float Camera::GetScale() const
{
	return scale;
}
