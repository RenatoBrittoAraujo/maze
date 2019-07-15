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

	/*
		Empties all data and generates a brand new labirinth
	 */
	void generateLabirinth();

	/*
		Draws labirinth to screen
	 */
	void draw(Graphics &graphics);

	/*
		Returns a vector of segments containing all labirinth's segments
	 */
	std::vector<Segment> getBarriers() const;

	/*
		Returns true if point passed is a victory condition
	 */
	bool victory(const Point playerPosition) const;

private:

	/*
		Grid vertical size and horizontal size
	 */
	int _vSize;
	int _hSize;

	std::vector<Segment> _barriers;

	/*
		Supporting dfs routine for generating the labirinth
	 */
	void dfs(int vertex, std::vector<bool> &visited, std::vector<Segment> &toDelete);

	const int getSquareId(const int x, const int y);
	const int getSquareX(const int id);
	const int getSquareY(const int id);
	const bool validatePosition(const int x, const int y);

	// Cardinal directions
	const int _dx[4] = {1, -1, 0, 0};
	const int _dy[4] =  {0, 0, 1, -1};
};

#endif