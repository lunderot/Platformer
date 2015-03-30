#include "Entity.h"


Entity::Entity(SDL_Texture* texture, Vec2f size, Vec2f position, Vec2f velocity, Vec2f acceleration)
{
	this->texture = texture;
	this->size = size;
	this->position = position;
	this->velocity = velocity;
	this->acceleration = acceleration;
}


Entity::~Entity()
{
}

Box Entity::GetBoundingBox() const
{
	return Box(position, size);
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
