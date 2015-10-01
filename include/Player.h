#pragma once
#include "Entity.h"

class Player : public Entity
{
public:
	Player(SDL_Texture* texture, float radius, glm::vec2 position = glm::vec2(), glm::vec2 velocity = glm::vec2(), glm::vec2 acceleration = glm::vec2());
	~Player();

	void Update(float deltaTime);
};

