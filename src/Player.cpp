#include "Player.h"


Player::Player(SDL_Texture* texture, glm::f32 radius, glm::f32 mass, glm::vec2 position)
	:Entity(texture, radius)
{
	this->physicsBody = new CircleBody(position, mass, radius);
}


Player::~Player()
{
	delete physicsBody;
}

void Player::Update(float deltaTime)
{
	physicsBody->Update(deltaTime);
}
