#include "labirinth.hpp"
#include "segment.hpp"
#include "point.hpp"
#include "globals.hpp"

#include <vector>
#include <assert.h>

namespace 
{
	// This represents the size of the labirinth's squared grid
	const int STEP = 50;
}

Labirinth::Labirinth()
{
	for(int i = 0; i <= globals::SCREEN_WIDTH; i += STEP)
	{
		for(int j = 0; j <= globals::SCREEN_HEIGHT; j += STEP)
		{
			this->_barriers.push_back( Segment( Point(i, j), Point(i + STEP, j) ) );
			this->_barriers.push_back( Segment( Point(i, j), Point(i, j + STEP) ) );
		}
	}
}

Labirinth::~Labirinth()
{}

void Labirinth::generateLabirinth()
{

}

void Labirinth::draw(Graphics &graphics)
{
	for (Segment &segment : this->_barriers)
	{
		segment.draw(graphics);
	}
}

void Labirinth::update()
{

}

std::vector<Segment> Labirinth::getBarriers() const
{
	return this->_barriers;
}