#pragma once

#include <SDL.h>

#include "math/Math.h"
#include "Entity.h"

class Entity
{
	friend class EntityHandler;
protected:
	SDL_Texture* texture;
	float radius;

	Vec2f position;
	Vec2f velocity;
	Vec2f acceleration;
public:
	Entity(SDL_Texture* texture, float radius, Vec2f position = Vec2f(), Vec2f velocity = Vec2f(), Vec2f acceleration = Vec2f());
	virtual ~Entity();

	virtual void Update(float deltaTime);
	virtual void Render(SDL_Renderer* renderer, Entity* camera);

	Circle GetBoundingCircle() const;

	void SetPosition(Vec2f position);
	void SetVelocity(Vec2f velocity);
	void SetAcceleration(Vec2f acceleration);

	Vec2f GetPosition() const;
	Vec2f GetVelocity() const;
	Vec2f GetAcceleration() const;

	float GetRadius() const;
};

