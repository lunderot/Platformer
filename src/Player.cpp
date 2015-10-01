#include "Player.h"


Player::Player(SDL_Texture* texture, float radius, glm::vec2 position, glm::vec2 velocity, glm::vec2 acceleration)
	:Entity(texture, radius, position, velocity, acceleration)
{
}


Player::~Player()
{
}

void Player::Update(float deltaTime)
{
	
}
