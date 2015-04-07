#include "Camera.h"


Camera::Camera(Vec2f size, Vec2f position) : Entity(nullptr, 0, position)
{
	this->size = size;
}


Camera::~Camera()
{
}

Vec2f Camera::GetSize()
{
	return size;
}
