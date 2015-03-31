#include "Entity.h"


Entity::Entity(SDL_Texture* texture, float radius, Vec2f position, Vec2f velocity, Vec2f acceleration)
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

void Entity::Render(SDL_Renderer* renderer)
{
	SDL_Rect destination =
	{
		static_cast<int>(position.x - radius),
		static_cast<int>(position.y - radius),
		static_cast<int>(radius * 2),
		static_cast<int>(radius * 2)
	};
	SDL_RenderCopy(renderer, texture, nullptr, &destination);
}

Circle Entity::GetBoundingCircle() const
{
	return Circle(position, radius);
}

void Entity::SetPosition(Vec2f position)
{
	this->position = position;
}

void Entity::SetVelocity(Vec2f velocity)
{
	this->velocity = velocity;
}

void Entity::SetAcceleration(Vec2f acceleration)
{
	this->acceleration = acceleration;
}

Vec2f Entity::GetPosition() const
{
	return position;
}

Vec2f Entity::GetVelocity() const
{
	return velocity;
}

Vec2f Entity::GetAcceleration() const
{
	return acceleration;
}
