#pragma once

#include <SDL.h>

#include "math/Math.h"

#include "physics/Body.h"
#include "physics/CircleBody.h"

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
	Body* physicsBody;

	SDL_Texture* texture;
	glm::f32 renderRadius;
	glm::vec2 renderPosition;
	glm::f32 renderAngle;
public:
	Entity(SDL_Texture* texture = nullptr, glm::f32 renderRadius = 0.0f, glm::vec2 renderPosition = glm::vec2(), glm::f32 renderAngle = 0.0f);
	virtual ~Entity();

	virtual void Update(float deltaTime);
	virtual void Render(SDL_Renderer* renderer, const glm::mat4& cameraMatrix, float scale);

	Body* GetPhysicsBody() const;

	glm::f32 GetRenderRadius() const;
	glm::vec2 GetRenderPosition() const;
	glm::f32 GetRenderAngle() const;

	void SetRenderPosition(glm::vec2 position);
};

