#include "EntityHandler.h"


EntityHandler::EntityHandler()
{
	Vec2f offset(500, 300);
	float factor = 400.0f;
	for (int i = 0; i < 18*10; i++)
	{
		float m = 20.0f * 0.0174532925f / 10.0f;
		collisionLines.push_back(new LineSegment(offset + Vec2f(cos(i * m)*factor, sin(i * m)*factor), offset + Vec2f(cos((i + 1) * m)*factor, sin((i + 1) * m)*factor)));
	}
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
					Vec2f out = incidentVec - lineNormal * (2.0f * incidentVec.Dot(lineNormal));

					(*i)->SetVelocity(out*0.9f);
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

Entity* EntityHandler::GetEntity(int id)
{
	return entities.at(id);
}

int EntityHandler::GetCameraId()
{
	return cameraId;
}
