#pragma once

#include <SDL.h>

#include "math/Math.h"

enum EntityType
{
	PLAYER,
	TILE,
	CAMERA,
	MARKER
};

class Entity
{
	friend class EntityHandler;
protected:
	SDL_Texture* texture;
	float radius;

	glm::vec2 position;
	glm::vec2 velocity;
	glm::vec2 acceleration;
public:
	Entity(SDL_Texture* texture, float radius, glm::vec2 position = glm::vec2(), glm::vec2 velocity = glm::vec2(), glm::vec2 acceleration = glm::vec2());
	virtual ~Entity();

	virtual void Update(float deltaTime);
	virtual void Render(SDL_Renderer* renderer, const glm::mat4& cameraMatrix, float scale);

	Circle GetBoundingCircle() const;

	void SetPosition(glm::vec2 position);
	void SetVelocity(glm::vec2 velocity);
	void SetAcceleration(glm::vec2 acceleration);

	glm::vec2 GetPosition() const;
	glm::vec2 GetVelocity() const;
	glm::vec2 GetAcceleration() const;

	float GetRadius() const;
};

