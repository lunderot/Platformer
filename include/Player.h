#pragma once
#include "Entity.h"

class Player : public Entity
{
public:
	Player(SDL_Texture* texture, float radius, Vec2f position = Vec2f(), Vec2f velocity = Vec2f(), Vec2f acceleration = Vec2f());
	~Player();

	void Update(float deltaTime);
};

