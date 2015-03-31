#include "math/Math.h"

float SweptAABB(Box box1, Vec2f box1vel, Box box2, Vec2f box2vel, Vec2f& normal)
{
	Vec2f invEntry;
	Vec2f invExit;

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

	Vec2f entry;
	Vec2f exit;
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

Vec2f ClosestPoint(LineSegment line, Circle circle)
{
	Vec2f seg = line.point[1] - line.point[0];
	Vec2f pt = circle.position - line.point[0];
	if (seg.Length() <= 0.0f)
	{
		throw std::runtime_error("Invalid line segment length");
	}
	Vec2f seg_unit = seg.Normalized();
	float proj = pt.Dot(seg_unit);
	if (proj <= 0.0f)
	{
		return line.point[0];
	}
	if (proj >= seg.Length())
	{
		return line.point[1];
	}
	Vec2f proj_v = seg_unit * proj;
	Vec2f closest = proj_v + line.point[0];
	return closest;
}

Vec2f LineSegmentCircleCollision(LineSegment line, Circle circle)
{
	Vec2f closest = ClosestPoint(line, circle);
	Vec2f dist = circle.position - closest;
	if (dist.Length() > circle.radius)
	{
		return Vec2f(0.0f, 0.0f);
	}
	if (dist.Length() <= 0.0f)
	{
		throw std::runtime_error("Circle's center is exactly on segment");
	}
	Vec2f offset = dist.Normalized() * (circle.radius - dist.Length());
	return offset;
}
