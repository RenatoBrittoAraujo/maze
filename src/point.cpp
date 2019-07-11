#include "point.hpp"

#include <math.h>

Point::Point()
{}

Point::~Point()
{}

Point::Point(float x, float y) :
	_x(x), _y(y)
{}

float Point::getX()
{
	return this->_x;
}

float Point::getY()
{
	return this->_y;
}

void Point::setX(float x)
{
	this->_x = x;
}

void Point::setY(float y)
{
	this->_y = y;
}

float Point::euclidianDistance(Point &other)
{
	return hypot(this->getX() - other.getX(), this->getY() - other.getY());
}