#pragma once
#include "Entity.h"

class Flipper : public Entity
{
public:
	Flipper(SDL_Texture* texture, glm::f32 length, glm::f32 mass, glm::vec2 position = glm::vec2());
	~Flipper();

	void Update(float deltaTime);
	void Render(SDL_Renderer* renderer, const glm::mat4& cameraMatrix, float scale);
};

