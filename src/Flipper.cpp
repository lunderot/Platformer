#include "Flipper.h"


Flipper::Flipper(SDL_Texture* texture, glm::f32 length, glm::f32 mass, glm::vec2 position) : Entity(texture)
{
	this->physicsBody = new LineBody(position, mass, length);
}


Flipper::~Flipper()
{
	delete physicsBody;
}

void Flipper::Update(float deltaTime)
{
	physicsBody->Update(deltaTime);
}

void Flipper::Render(SDL_Renderer* renderer, const glm::mat4& cameraMatrix, float scale)
{
	if (physicsBody)
	{
		renderPosition = physicsBody->GetPosition();
		renderAngle = physicsBody->GetAngle();
		glm::f32 length;
		LineBody* line = dynamic_cast<LineBody*>(physicsBody);
		if (line)
		{
			length = line->GetLength();
		}

		glm::vec4 translatedPoint0 = cameraMatrix * glm::vec4(renderPosition.x, renderPosition.y, 1, 1);
		glm::vec4 translatedPoint1 = cameraMatrix * glm::vec4((renderPosition.x + length) * glm::cos(renderAngle), (renderPosition.y + length) * glm::sin(renderAngle), 1, 1);

		SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawLine(renderer,
			static_cast<int>(translatedPoint0.x),
			static_cast<int>(translatedPoint0.y),
			static_cast<int>(translatedPoint1.x),
			static_cast<int>(translatedPoint1.y)
			);
	}
}
