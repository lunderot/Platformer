#include "EntityHandler.h"


EntityHandler::EntityHandler()
{
	collisionLines.push_back(new LineSegment(Vec2f(0, 0), Vec2f(500, 400)));
	collisionLines.push_back(new LineSegment(Vec2f(500, 400), Vec2f(1000, 400)));
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

				(*i)->SetVelocity(out);
			}
		}
	}
}

void EntityHandler::Render(SDL_Renderer* renderer)
{
	for (std::vector<Entity*>::iterator i = entities.begin(); i != entities.end(); ++i)
	{
		(*i)->Render(renderer);
	}
	for (std::vector<LineSegment*>::iterator j = collisionLines.begin(); j != collisionLines.end(); ++j)
	{
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawLine(renderer, (*j)->point[0].x, (*j)->point[0].y, (*j)->point[1].x, (*j)->point[1].y);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	}
	
}

void EntityHandler::Add(Entity* entity)
{
	entities.push_back(entity);
}
