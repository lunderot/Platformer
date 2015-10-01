#include "math/Math.h"

float SweptAABB(Box box1, glm::vec2 box1vel, Box box2, glm::vec2 box2vel, glm::vec2& normal)
{
	glm::vec2 invEntry;
	glm::vec2 invExit;

	if (box1vel.x > 0.0f)
	{
		invEntry.x = box2.position.x - (box1.position.x + box1.size.x);
		invExit.x = (box2.position.x + box2.size.x) + box1.position.x;
	}
	else
	{
		invEntry.x = (box2.position.x + box2.size.x) - box1.position.x;
		invExit.x = box2.position.x - (box1.position.x + box1.size.x);
	}

	if (box1vel.y > 0.0f)
	{
		invEntry.y = box2.position.y - (box1.position.y + box1.size.y);
		invExit.y = (box2.position.y + box2.size.y) + box1.position.y;
	}
	else
	{
		invEntry.y = (box2.position.y + box2.size.y) - box1.position.y;
		invExit.y = box2.position.y - (box1.position.y + box1.size.y);
	}

	glm::vec2 entry;
	glm::vec2 exit;
	if (box1vel.x == 0.0f)
	{
		entry.x = -std::numeric_limits<float>::infinity();
		exit.x = std::numeric_limits<float>::infinity();
	}
	else
	{
		entry.x = invEntry.x / box1vel.x;
		exit.x = invExit.x / box1vel.x;
	}

	if (box1vel.y == 0.0f)
	{
		entry.y = -std::numeric_limits<float>::infinity();
		exit.y = std::numeric_limits<float>::infinity();
	}
	else
	{
		entry.y = invEntry.y / box1vel.y;
		exit.y = invExit.y / box1vel.y;
	}

	float entryTime = std::max(entry.x, entry.y);
	float exitTime = std::max(exit.x, exit.y);

	if (entryTime > exitTime || entry.x < 0.0f && entry.y < 0.0f || entry.x > 1.0f || entry.y > 1.0f)
	{
		normal.x = 0.0f;
		normal.y = 0.0f;
		return 1.0f;
	}
	else
	{
		if (entry.x > entry.y)
		{
			if (invEntry.x < 0.0f)
			{
				normal.x = 1.0f;
				normal.y = 0.0f;
			}
			else
			{
				normal.x = -1.0f;
				normal.y = 0.0f;
			}
		}
		else
		{
			if (invEntry.y < 0.0f)
			{
				normal.x = 0.0f;
				normal.y = 1.0f;
			}
			else
			{
				normal.x = 0.0f;
				normal.y = -1.0f;
			}
		}
		return entryTime;
	}
}

glm::vec2 ClosestPoint(LineSegment line, Circle circle)
{
	glm::vec2 seg = line.point[1] - line.point[0];
	glm::vec2 pt = circle.position - line.point[0];
	if (glm::length(seg) <= 0.0f)
	{
		throw std::runtime_error("Invalid line segment length");
	}
	glm::vec2 seg_unit = glm::normalize(seg);
	float proj = glm::dot(pt, seg_unit);
	if (proj <= 0.0f)
	{
		return line.point[0];
	}
	if (proj >= glm::length(seg))
	{
		return line.point[1];
	}
	glm::vec2 proj_v = seg_unit * proj;
	glm::vec2 closest = proj_v + line.point[0];
	return closest;
}

glm::vec2 LineSegmentCircleCollision(LineSegment line, Circle circle)
{
	glm::vec2 closest = ClosestPoint(line, circle);
	glm::vec2 dist = circle.position - closest;
	if (glm::length(dist) > circle.radius)
	{
		return glm::vec2(0.0f, 0.0f);
	}
	if (glm::length(dist) <= 0.0f)
	{
		throw std::runtime_error("Circle's center is exactly on segment");
	}
	glm::vec2 offset = glm::normalize(dist) * (circle.radius - glm::length(dist));
	return offset;
}
