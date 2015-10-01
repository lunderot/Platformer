#pragma once
#include "Entity.h"
class Tile : public Entity
{
public:
	Tile(SDL_Texture* texture, float size, glm::vec2 position = glm::vec2());
	~Tile();
};

