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

		if (!dynamic_cast<Tile*>((*i))) //Don't check physics for tiles
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
		(*i)->Render(renderer);
	}
	for (std::vector<LineSegment*>::iterator j = collisionLines.begin(); j != collisionLines.end(); ++j)
	{
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawLine(renderer, (*j)->point[0].x, (*j)->point[0].y, (*j)->point[1].x, (*j)->point[1].y);
	}
	
}

void EntityHandler::Add(Entity* entity)
{
	entities.push_back(entity);
}

Entity* EntityHandler::GetEntity(int id)
{
	return entities.at(id);
}
