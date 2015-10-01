#include "math\LineSegment.h"


LineSegment::LineSegment(glm::vec2 point1, glm::vec2 point2)
{
	point[0] = point1;
	point[1] = point2;
}


LineSegment::~LineSegment()
{
}
