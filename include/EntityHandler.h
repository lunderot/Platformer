#pragma once

#include <vector>
#include <fstream>

#include "Entity.h"
#include "Tile.h"
#include "Camera.h"
#include "Player.h"

#include "AssetHandler.h"

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
	int Add(EntityType type, std::string textureFilename, float radius, AssetHandler* assetHandler);
	void AddCollisionLine(LineSegment* line);

	Entity* GetEntity(int id);
	int GetCameraId();

	void SaveToFile(std::string filename, AssetHandler* assetHandler);
};

