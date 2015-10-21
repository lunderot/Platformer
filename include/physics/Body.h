#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <vector>

#include "Impulse.h"
#include "AngularImpulse.h"
#include "Moment.h"

class Body
{
protected:
	glm::vec2 position;
	glm::vec2 velocity;
	glm::vec2 acceleration;
	glm::f32 angle;
	glm::f32 angularVelocity;
	glm::f32 angularAcceleration;

	glm::f32 mass;

	std::vector<Impulse> impulses;
	std::vector<AngularImpulse> angularImpulses;

	std::vector<glm::vec2> forces;
	std::vector<Moment> moments;
public:
	Body(glm::vec2 position, glm::f32 mass);
	virtual ~Body();

	void Update(glm::f32 deltaTime);
	virtual glm::f32 GetInertia() const = 0;

	void ApplyForce(glm::vec2 force, glm::vec2 offset);
	void ApplyForce(glm::vec2 force);
	void ApplyImpulse(glm::vec2 force, glm::f32 time, glm::vec2 offset);
	void ApplyImpulse(glm::vec2 force, glm::f32 time);

	void SetPosition(glm::vec2 position);
	glm::vec2 GetPosition() const;

	void SetVelocity(glm::vec2 velocity);
	glm::vec2 GetVelocity() const;

	void SetAcceleration(glm::vec2 acceleration);
	glm::vec2 GetAcceleration() const;

	void SetAngle(glm::f32 angle);
	glm::f32 GetAngle() const;

	void SetAngularVelocity(glm::f32 angularVelocity);
	glm::f32 GetAngularVelocity() const;

	void SetAngularAcceleration(glm::f32 angularAcceleration);
	glm::f32 GetAngularAcceleration() const;

	glm::f32 GetMass() const;
};

