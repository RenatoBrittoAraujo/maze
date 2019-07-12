#ifndef SEGMENT_HPP
#define SEGMENT_HPP

#include "point.hpp"
#include "graphics.hpp"

class Segment
{
public:

	Segment();
	~Segment();

	Segment(Point first, Point second);

	void draw(Graphics &graphics);
	void update();

	Point getFirst() { return this->_first; }
	Point getSecond() { return this->_second; }

private:

	Point _first;
	Point _second;

};

#endif