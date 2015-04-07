#pragma once
#include "Entity.h"
class Camera : public Entity
{
private:
	Vec2f size;
public:
	Camera(Vec2f size, Vec2f position = Vec2f());
	~Camera();

	Vec2f GetSize();
};

