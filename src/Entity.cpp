#include "Entity.h"

#include "Camera.h"

Entity::Entity(SDL_Texture* texture, glm::f32 renderRadius, glm::vec2 renderPosition, glm::f32 renderAngle)
{
	this->texture = texture;
	this->renderRadius = renderRadius;
	this->physicsBody = nullptr;
	this->renderPosition = renderPosition;
	this->renderAngle = renderAngle;
}


Entity::~Entity()
{
}

void Entity::Update(float deltaTime)
{
}

void Entity::Render(SDL_Renderer* renderer, const glm::mat4& cameraMatrix, float scale)
{
	if (texture)
	{
		if (physicsBody)
		{
			renderPosition = physicsBody->GetPosition();
			renderAngle = physicsBody->GetAngle();
		}
		glm::vec4 translatedPoint0 = cameraMatrix * glm::vec4((renderPosition.x - renderRadius), (renderPosition.y - renderRadius), 1, 1);
		SDL_Rect destination =
		{
			static_cast<int>(translatedPoint0.x),
			static_cast<int>(translatedPoint0.y),
			static_cast<int>(renderRadius * 2 * scale),
			static_cast<int>(renderRadius * 2 * scale)
		};
		SDL_RenderCopyEx(renderer, texture, nullptr, &destination, glm::degrees(renderAngle), nullptr, SDL_FLIP_NONE);
	}
}

Body* Entity::GetPhysicsBody() const
{
	return physicsBody;
}

glm::f32 Entity::GetRenderRadius() const
{
	return renderRadius;
}
glm::vec2 Entity::GetRenderPosition() const
{
	return renderPosition;
}
glm::f32 Entity::GetRenderAngle() const
{
	return renderAngle;
}
