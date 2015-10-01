#pragma once
#include "Entity.h"
class Marker :
	public Entity
{
public:
	Marker(SDL_Texture* texture, float radius, glm::vec2 position = glm::vec2(), glm::vec2 velocity = glm::vec2(), glm::vec2 acceleration = glm::vec2());
	~Marker();

	void SetTexture(SDL_Texture* texture);
};

