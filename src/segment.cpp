#include "segment.hpp"
#include "point.hpp"

#include <SDL2/SDL.h>

Segment::Segment()
{}

Segment::~Segment()
{}

Segment::Segment(Point first, Point second) :
	_first(first), _second(second)
{}

void Segment::draw(Graphics &graphics)
{
	SDL_RenderDrawLine(graphics.getRenderer(), _first.getX(), _first.getY(), _second.getX(), _second.getY());
}

void Segment::update()
{

}