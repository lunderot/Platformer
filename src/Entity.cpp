#include "Entity.h"

#include "Camera.h"

Entity::Entity(SDL_Texture* texture, float radius, glm::vec2 position, glm::vec2 velocity, glm::vec2 acceleration)
{
	this->texture = texture;
	this->radius = radius;
	this->position = position;
	this->velocity = velocity;
	this->acceleration = acceleration;
}


Entity::~Entity()
{
}

void Entity::Update(float deltaTime)
{

}

void Entity::Render(SDL_Renderer* renderer, const glm::mat4& cameraMatrix, float scale)
{
	glm::vec4 translatedPoint0 = cameraMatrix * glm::vec4((position.x - radius), (position.y - radius), 1, 1);
	//glm::vec4 translatedPoint1 = scaleMatrix * glm::vec4(radius * 2, radius * 2, 1, 1);
	SDL_Rect destination =
	{
		static_cast<int>(translatedPoint0.x),
		static_cast<int>(translatedPoint0.y),
		static_cast<int>(radius * 2 * scale),
		static_cast<int>(radius * 2 * scale)
	};
	SDL_RenderCopy(renderer, texture, nullptr, &destination);
}

Circle Entity::GetBoundingCircle() const
{
	return Circle(position, radius);
}

void Entity::SetPosition(glm::vec2 position)
{
	this->position = position;
}

void Entity::SetVelocity(glm::vec2 velocity)
{
	this->velocity = velocity;
}

void Entity::SetAcceleration(glm::vec2 acceleration)
{
	this->acceleration = acceleration;
}

glm::vec2 Entity::GetPosition() const
{
	return position;
}

glm::vec2 Entity::GetVelocity() const
{
	return velocity;
}

glm::vec2 Entity::GetAcceleration() const
{
	return acceleration;
}

float Entity::GetRadius() const
{
	return radius;
}
