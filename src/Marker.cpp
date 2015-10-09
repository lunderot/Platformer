#include "Marker.h"


Marker::Marker(SDL_Texture* texture, glm::f32 radius, glm::vec2 position)
	:Entity(texture, radius, position)
{
	
}


Marker::~Marker()
{
}

void Marker::SetTexture(SDL_Texture* texture)
{
	this->texture = texture;
}
