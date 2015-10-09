#pragma once
#include "Entity.h"

class Player : public Entity
{
public:
	Player(SDL_Texture* texture, glm::f32 radius, glm::f32 mass, glm::vec2 position = glm::vec2());
	~Player();

	void Update(float deltaTime);
};

