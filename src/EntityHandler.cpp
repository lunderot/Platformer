#include "EntityHandler.h"


EntityHandler::EntityHandler()
{
	entityIndex = 0;
	cameraId = -1;
}


EntityHandler::~EntityHandler()
{
	for (std::map<unsigned int, Entity*>::iterator i = entities.begin(); i != entities.end(); ++i)
	{
		delete (*i).second;
	}
	for (std::vector<LineSegment*>::iterator j = collisionLines.begin(); j != collisionLines.end(); ++j)
	{
		delete *j;
	}
}

void EntityHandler::Update(float deltaTime)
{
	for (std::map<unsigned int, Entity*>::iterator i = entities.begin(); i != entities.end(); ++i)
	{
		(*i).second->Update(deltaTime);
	}
}

void EntityHandler::Render(SDL_Renderer* renderer)
{
	Camera* cam = dynamic_cast<Camera*>(GetEntity(cameraId));
	glm::mat4 cameraMatrix = cam->GetCameraMatrix();
	float scale = cam->GetScale();
	for (std::map<unsigned int, Entity*>::iterator i = entities.begin(); i != entities.end(); ++i)
	{
		(*i).second->Render(renderer, cameraMatrix, scale);
	}

	for (std::vector<LineSegment*>::iterator j = collisionLines.begin(); j != collisionLines.end(); ++j)
	{
		glm::vec4 translatedPoint0 = cameraMatrix * glm::vec4((*j)->point[0], 1, 1);
		glm::vec4 translatedPoint1 = cameraMatrix * glm::vec4((*j)->point[1], 1, 1);

		SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawLine(renderer,
			static_cast<int>(translatedPoint0.x),
			static_cast<int>(translatedPoint0.y),
			static_cast<int>(translatedPoint1.x),
			static_cast<int>(translatedPoint1.y)
		);
	}
}

int EntityHandler::Add(Entity* entity)
{
	int returnValue = -1;
	returnValue = entityIndex;
	entities.insert(std::pair<unsigned int, Entity*>(entityIndex, entity));
	entityIndex++;

	if (dynamic_cast<Camera*>(entity))
	{
		if (cameraId == -1)
		{
			cameraId = returnValue;
		}
		else
		{
			throw std::runtime_error("More than one camera added");
		}
	}
	return returnValue;
}

int EntityHandler::Add(EntityType type, std::string textureFilename, float radius, AssetHandler* assetHandler)
{
	Entity* entity = nullptr;
	switch (type)
	{
	case PLAYER:
		entity = new Player(assetHandler->GetTexture(textureFilename), radius, 10);
		break;
	case TILE:
		entity = new Tile(assetHandler->GetTexture(textureFilename), radius);
		break;
	case MARKER:
		entity = new Marker(assetHandler->GetTexture(textureFilename), radius);
		break;
	default:
		break;
	}
	if (!entity)
	{
		throw std::runtime_error("Invalid entity type");
	}
	return Add(entity);
}

void EntityHandler::AddCollisionLine(LineSegment* line)
{
	collisionLines.push_back(line);
}

bool EntityHandler::Remove(unsigned int id)
{
	bool returnValue = false;
	std::map<unsigned int, Entity*>::iterator it = entities.find(id);

	if (it != entities.end())
	{
		entities.erase(it);
		returnValue = true;
	}
	return returnValue;
}

Entity* EntityHandler::GetEntity(unsigned int id)
{
	return entities[id];
}

int EntityHandler::GetCameraId()
{
	return cameraId;
}

int EntityHandler::GetFirstPlayerId()
{
	for (std::map<unsigned int, Entity*>::iterator i = entities.begin(); i != entities.end(); ++i)
	{
		if (dynamic_cast<Player*>((*i).second))
		{
			return (*i).first;
		}
	}
	return -1;
}

void EntityHandler::SaveToFile(std::string filename, AssetHandler* assetHandler)
{
	std::ofstream file(filename);
	if (file.good())
	{
		//Save entities
		for (std::map<unsigned int, Entity*>::iterator i = entities.begin(); i != entities.end(); ++i)
		{
			Tile* tile = dynamic_cast<Tile*>((*i).second);
			if (tile)
			{
				glm::vec2 position = tile->GetRenderPosition();
				file << "t " << assetHandler->GetFilenameFromPointer(tile->texture) << " " << position.x << " " << position.y;
				file << std::endl;
			}
			
		}
		//Save collision lines
		for (std::vector<LineSegment*>::iterator i = collisionLines.begin(); i != collisionLines.end(); ++i)
		{
			file << std::endl;
			file << "l "
				<< (*i)->point[0].x << " "
				<< (*i)->point[0].y << " "
				<< (*i)->point[1].x << " "
				<< (*i)->point[1].y;
			
		}
	}
	else
	{
		throw std::runtime_error("Failed to create: " + filename);
	}
	file.close();
}

