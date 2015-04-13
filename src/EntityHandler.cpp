#include "EntityHandler.h"


EntityHandler::EntityHandler()
{
	cameraId = -1;
}


EntityHandler::~EntityHandler()
{
	for (std::vector<Entity*>::iterator i = entities.begin(); i != entities.end(); ++i)
	{
		delete *i;
	}
	for (std::vector<LineSegment*>::iterator j = collisionLines.begin(); j != collisionLines.end(); ++j)
	{
		delete *j;
	}
}

void EntityHandler::Update(float deltaTime)
{
	for (std::vector<Entity*>::iterator i = entities.begin(); i != entities.end(); ++i)
	{
		(*i)->Update(deltaTime);

		if (dynamic_cast<Player*>((*i))) //Don't check physics for tiles and camera
		{
			(*i)->velocity += (*i)->acceleration * deltaTime;
			(*i)->position += (*i)->velocity * deltaTime;

			//Check and resolve collision with lines
			for (std::vector<LineSegment*>::iterator j = collisionLines.begin(); j != collisionLines.end(); ++j)
			{
				//Calculate offset and move entity
				Vec2f offset = LineSegmentCircleCollision(*(*j), (*i)->GetBoundingCircle());
				(*i)->position += offset;

				if (offset.Length() > 0.0f)
				{
					//Calculate line normal
					Vec2f lineNormal = offset.Normalized();

					//Calculate reflection vector
					Vec2f incidentVec = (*i)->GetVelocity();
					Vec2f out = incidentVec + lineNormal;

					(*i)->SetVelocity(out);
				}
			}
		}
	}
}

void EntityHandler::Render(SDL_Renderer* renderer)
{
	for (std::vector<Entity*>::iterator i = entities.begin(); i != entities.end(); ++i)
	{
		(*i)->Render(renderer, GetEntity(cameraId));
	}
	Camera* cam = dynamic_cast<Camera*>(GetEntity(cameraId));
	Vec2f cameraPosition = GetEntity(cameraId)->GetPosition();
	Vec2f cameraSize = cam->GetSize();
	for (std::vector<LineSegment*>::iterator j = collisionLines.begin(); j != collisionLines.end(); ++j)
	{
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawLine(renderer,
			(*j)->point[0].x - cameraPosition.x + cameraSize.x/2,
			(*j)->point[0].y - cameraPosition.y + cameraSize.y/2,
			(*j)->point[1].x - cameraPosition.x + cameraSize.x/2,
			(*j)->point[1].y - cameraPosition.y + cameraSize.y/2
		);
	}
}

int EntityHandler::Add(Entity* entity)
{
	int returnValue = -1;
	returnValue = entities.size();
	entities.push_back(entity);

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
		entity = new Player(assetHandler->GetTexture(textureFilename), radius);
		break;
	case TILE:
		entity = new Tile(assetHandler->GetTexture(textureFilename), radius);
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

Entity* EntityHandler::GetEntity(int id)
{
	return entities.at(id);
}

int EntityHandler::GetCameraId()
{
	return cameraId;
}
