#include "Player.h"


Player::Player(SDL_Texture* texture, Vec2f size, Vec2f position, Vec2f velocity, Vec2f acceleration)
	:Entity(texture, size, position, velocity, acceleration)
{
}


Player::~Player()
{
}

void Player::Update(float deltaTime)
{
	
}
