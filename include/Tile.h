#pragma once
#include "Entity.h"
class Tile : public Entity
{
public:
	Tile(SDL_Texture* texture, float size, Vec2f position = Vec2f());
	~Tile();
};

