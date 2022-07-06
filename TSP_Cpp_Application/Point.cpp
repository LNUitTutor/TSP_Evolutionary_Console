#include "Point.h"

std::ostream& operator<<(std::ostream& os, const Point& p)
{
	(os << " (").width(4);
	(os << p.x << ',').width(4);
	os << p.y << ')';
	return os;
}