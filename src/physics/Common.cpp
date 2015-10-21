#include "physics/Common.h"

void CircleLineCollision(CircleBody* circle, LineSegment* line)
{
	glm::f32 radius = circle->GetRadius();
	glm::vec2 center = circle->GetPosition();
	glm::vec2 point0 = line->point[0];
	glm::vec2 point1 = line->point[1];

	glm::vec2 normal(
		(point1.y - point0.y)*-1.0f,
		(point1.x - point0.x)
		);
	normal = glm::normalize(normal);

	glm::f32 distance = glm::dot(center - point0, normal);

	//Always point the normal towards the circle
	normal = normal * glm::sign(distance);

	if (glm::abs(distance) < radius)
	{
		glm::vec2 line = point1 - point0;
		glm::f32 len = glm::length(line);
		glm::vec2 b = glm::normalize(line);
		glm::vec2 proj = glm::dot(center - point0, b) * b;


		glm::f32 result = glm::dot(line, proj) / len;

		if (result > -1.0f * radius &&
			result < len + radius)
		{
			//Collision has occurred
			//Set the velocity to the reflection vector
			glm::vec2 i = circle->GetVelocity();
			circle->SetVelocity(i - 2.0f * normal * glm::dot(normal, i) * 0.8f);

			//Move the circle back to not collide with the line again
			glm::f32 moveBackDistance = 1.0f;
			circle->SetPosition(circle->GetPosition() + glm::normalize(i) * moveBackDistance * -1.0f);
		}

	}
}