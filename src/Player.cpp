#include "Player.h"


Player::Player(SDL_Texture* texture, float radius, Vec2f position, Vec2f velocity, Vec2f acceleration)
	:Entity(texture, radius, position, velocity, acceleration)
{
}


Player::~Player()
{
}

void Player::Update(float deltaTime)
{
	
}
