#include "segment.hpp"
#include "point.hpp"
#include "util.hpp"

#include <SDL2/SDL.h>

Segment::Segment()
{}

Segment::~Segment()
{}

Segment::Segment(Point first, Point second)
{
	this->_first = first;
	this->_second = second;
	if(second < first)
	{
		std::swap(this->_first, this->_second);
	}
}

void Segment::draw(Graphics &graphics)
{
	SDL_RenderDrawLine(graphics.getRenderer(),
		_first.getX(),
		_first.getY(),
		_second.getX(),
		_second.getY());
}

void Segment::scale(float scaleValue)
{
	this->_first.scale(scaleValue);
	this->_second.scale(scaleValue);
}