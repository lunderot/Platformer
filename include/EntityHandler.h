#pragma once

#include <vector>
#include <map>
#include <fstream>

#include "Entity.h"
#include "Tile.h"
#include "Camera.h"
#include "Player.h"
#include "Marker.h"

#include "AssetHandler.h"

class EntityHandler
{
	std::map<unsigned int, Entity*> entities;
	unsigned int entityIndex;
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

	bool Remove(unsigned int id);

	Entity* GetEntity(unsigned int id);
	int GetCameraId();

	int GetFirstPlayerId();

	void SaveToFile(std::string filename, AssetHandler* assetHandler);
};

