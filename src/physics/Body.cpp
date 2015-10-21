#include "physics/Body.h"


Body::Body(glm::vec2 position, glm::f32 mass)
{
	this->position = position;
	this->mass = mass;
}


Body::~Body()
{
}

void Body::Update(glm::f32 deltaTime)
{
	glm::vec2 totalForce(0.0f, 0.0f);
	glm::f32 totalMoment = 0.0f;

	//Add all forces together
	for (auto f = forces.begin(); f != forces.end(); ++f)
	{
		totalForce += *f;
	}

	//Add impulses to the total force and decrese time. Remove if time < 0
	{
		auto i = impulses.begin();
		while (i != impulses.end())
		{
			totalForce += i->force;
			i->time -= deltaTime;
			if (i->time < 0.0f)
			{
				i = impulses.erase(i);
			}
			else
			{
				++i;
			}
		}
	}

	//Add moments together
	for (auto i = moments.begin(); i != moments.end(); ++i)
	{
		//a = M/I = DxF/I
		totalMoment += (i->offset.x * i->force.y - i->offset.y * i->force.x);
	}

	//Add moment impulses and decrese time. Remove if time < 0
	auto ai = angularImpulses.begin();
	while (ai != angularImpulses.end())
	{
		totalMoment += (ai->offset.x * ai->force.y - ai->offset.y * ai->force.x);
		ai->time -= deltaTime;
		if (ai->time < 0.0f)
		{
			ai = angularImpulses.erase(ai);
		}
		else
		{
			++ai;
		}
	}

	acceleration = totalForce / mass;
	velocity += acceleration * deltaTime;
	position += velocity * deltaTime;

	angularAcceleration = totalMoment / GetInertia();
	angularVelocity += angularAcceleration * deltaTime;
	angle += angularVelocity * deltaTime;
	if (angle >= glm::two_pi<glm::f32>())
	{
		angle = 0.0f;
	}
	else if (angle <= 0.0f)
	{
		angle = glm::two_pi<glm::f32>();
	}
}

void Body::ApplyForce(glm::vec2 force, glm::vec2 offset)
{
	glm::f32 dot = glm::dot(force, offset);
	if (dot == -1.0f || dot == 1.0f) //This is the same as applying a force at center of mass, i.e. no moment
	{
		ApplyForce(force);
	}
	else
	{
		moments.push_back(Moment(force, offset));
	}
}

void Body::ApplyForce(glm::vec2 force)
{
	forces.push_back(force);
}

void Body::ApplyImpulse(glm::vec2 force, glm::f32 time, glm::vec2 offset)
{
	glm::f32 dot = glm::dot(force, offset);
	if (dot == -1.0f || dot == 1.0f)
	{
		ApplyImpulse(force, time);
	}
	else
	{
		angularImpulses.push_back(AngularImpulse(force, offset, time));
	}
}

void Body::ApplyImpulse(glm::vec2 force, glm::f32 time)
{
	impulses.push_back(Impulse(force, time));
}

void Body::SetPosition(glm::vec2 position)
{
	this->position = position;
}

glm::vec2 Body::GetPosition() const
{
	return position;
}

void Body::SetVelocity(glm::vec2 velocity)
{
	this->velocity = velocity;
}

glm::vec2 Body::GetVelocity() const
{
	return velocity;
}

void Body::SetAcceleration(glm::vec2 acceleration)
{
	this->acceleration = acceleration;
}
glm::vec2 Body::GetAcceleration() const
{
	return acceleration;
}

void Body::SetAngle(glm::f32 angle)
{
	this->angle = angle;
}

glm::f32 Body::GetAngle() const
{
	return angle;
}

void Body::SetAngularVelocity(glm::f32 angularVelocity)
{
	this->angularVelocity = angularVelocity;
}

glm::f32 Body::GetAngularVelocity() const
{
	return angularVelocity;
}

void Body::SetAngularAcceleration(glm::f32 angularAcceleration)
{
	this->angularAcceleration = angularAcceleration;
}

glm::f32 Body::GetAngularAcceleration() const
{
	return angularAcceleration;
}

glm::f32 Body::GetMass() const
{
	return mass;
}