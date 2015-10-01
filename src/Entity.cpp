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

void Entity::Render(SDL_Renderer* renderer, Entity* camera)
{
	glm::vec2 cameraPosition = camera->GetPosition();
	glm::vec2 cameraSize = dynamic_cast<Camera*>(camera)->GetSize();
	SDL_Rect destination =
	{
		static_cast<int>((position.x - radius) - cameraPosition.x + cameraSize.x/2),
		static_cast<int>((position.y - radius) - cameraPosition.y + cameraSize.y/2),
		static_cast<int>(radius * 2),
		static_cast<int>(radius * 2)
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
