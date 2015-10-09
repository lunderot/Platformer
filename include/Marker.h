#pragma once
#include "Entity.h"
class Marker :
	public Entity
{
public:
	Marker(SDL_Texture* texture, glm::f32 radius, glm::vec2 position = glm::vec2());
	~Marker();

	void SetTexture(SDL_Texture* texture);
};

