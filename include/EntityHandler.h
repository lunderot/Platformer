#pragma once

#include <vector>

#include "Entity.h"
#include "Tile.h"
#include "Camera.h"
#include "Player.h"

class EntityHandler
{
	std::vector<Entity*> entities;
	std::vector<LineSegment*> collisionLines;
	int cameraId;
public:
	EntityHandler();
	~EntityHandler();

	void Update(float deltaTime);
	void Render(SDL_Renderer* renderer);

	int Add(Entity* entity);

	Entity* GetEntity(int id);
};

