#include "Marker.h"


Marker::Marker(SDL_Texture* texture, float radius, glm::vec2 position, glm::vec2 velocity, glm::vec2 acceleration)
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
