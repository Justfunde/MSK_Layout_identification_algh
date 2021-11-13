#include "Point.h"
Point::Point(int x, int y)
{
	this->x = x;
	this->y = y;
}
Point::Point(const Point& cpy)
{
	this->x = cpy.x;
	this->y = cpy.y;
}

