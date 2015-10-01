#include "Camera.h"


Camera::Camera(glm::vec2 size, glm::vec2 position) : Entity(nullptr, 0, position)
{
	this->size = size;
}


Camera::~Camera()
{
}

glm::vec2 Camera::GetSize()
{
	return size;
}
