#pragma once
#include "Entity.h"
class Camera : public Entity
{
public:
	Camera(Vec2f position = Vec2f());
	~Camera();
};

