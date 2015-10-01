#include "Tile.h"


Tile::Tile(SDL_Texture* texture, float size, glm::vec2 position) :Entity(texture, size/2.0f, position)
{
}


Tile::~Tile()
{
}
