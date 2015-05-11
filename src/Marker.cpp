#include "Marker.h"


Marker::Marker(SDL_Texture* texture, float radius, Vec2f position, Vec2f velocity, Vec2f acceleration)
	:Entity(texture, radius, position, velocity, acceleration)
{
}


Marker::~Marker()
{
}

void Marker::SetTexture(SDL_Texture* texture)
{
	this->texture = texture;
}
