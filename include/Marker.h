#pragma once
#include "Entity.h"
class Marker :
	public Entity
{
public:
	Marker(SDL_Texture* texture, float radius, Vec2f position = Vec2f(), Vec2f velocity = Vec2f(), Vec2f acceleration = Vec2f());
	~Marker();

	void SetTexture(SDL_Texture* texture);
};

