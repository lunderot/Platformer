#include "EntityHandler.h"


EntityHandler::EntityHandler()
{
}


EntityHandler::~EntityHandler()
{
	for (std::vector<Entity*>::iterator i = entities.begin(); i != entities.end(); ++i)
	{
		delete *i;
	}
}

void EntityHandler::Update(float deltaTime)
{
	for (std::vector<Entity*>::iterator i = entities.begin(); i != entities.end(); ++i)
	{
		(*i)->Update(deltaTime);

		(*i)->velocity += (*i)->acceleration * deltaTime;
		(*i)->position += (*i)->velocity * deltaTime;
	}
}

void EntityHandler::Render(SDL_Renderer* renderer)
{
	for (std::vector<Entity*>::iterator i = entities.begin(); i != entities.end(); ++i)
	{
		(*i)->Render(renderer);
	}
}

void EntityHandler::Add(Entity* entity)
{
	entities.push_back(entity);
}
