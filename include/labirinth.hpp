#ifndef LABIRINTH_HPP
#define LABIRINTH_HPP

#include "graphics.hpp"
#include "segment.hpp"
#include "point.hpp"
#include <vector>

class Labirinth
{
public:

	Labirinth();
	~Labirinth();

	void generateLabirinth();

	void draw(Graphics &graphics);
	void update();

	std::vector<Segment> getBarriers() const;

private:

	std::vector<Segment> _barriers;
	
};

#endif