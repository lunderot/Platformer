#include "Tile.h"


Tile::Tile(SDL_Texture* texture, float size, Vec2f position) :Entity(texture, size/2.0f, position)
{
}


Tile::~Tile()
{
}
