#pragma once

#include <vector>

#include "Entity.h"

class EntityHandler
{
	std::vector<Entity*> entities;
public:
	EntityHandler();
	~EntityHandler();

	void Update(float deltaTime);
	void Render(SDL_Renderer* renderer);

	void Add(Entity* entity);
};

