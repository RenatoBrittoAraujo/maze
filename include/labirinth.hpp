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

	bool victory(const Point playerPosition) const;

private:

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