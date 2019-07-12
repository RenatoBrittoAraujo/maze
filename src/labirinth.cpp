#include "labirinth.hpp"
#include "segment.hpp"
#include "point.hpp"
#include "globals.hpp"
#include "util.hpp"

#include <vector>
#include <map>
#include <algorithm>

namespace 
{
	// This represents the size of the labirinth's squared grid
	const int STEP = 40;
}

Labirinth::Labirinth()
{
	_vSize = globals::SCREEN_HEIGHT / STEP;
	_hSize = globals::SCREEN_WIDTH / STEP;
}

Labirinth::~Labirinth()
{}

void Labirinth::draw(Graphics &graphics)
{
	for (Segment segment : this->_barriers)
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

#include <iostream>

void Labirinth::generateLabirinth()
{
	this->_barriers.clear();

	for(int i = 0; i <= _hSize; i++)
	{
		for(int j = 0; j <= _vSize; j++)
		{
			if(i < _hSize)
			{
				this->_barriers.push_back(Segment(Point(i, j), Point(i + 1, j)));
			}
			if(j < _vSize)
			{
				this->_barriers.push_back(Segment(Point(i, j), Point(i, j + 1)));
			}
		}
	}

	std::sort(this->_barriers.begin(), this->_barriers.end());

	std::vector<bool> visited(_vSize * _hSize + 1, false);
	std::vector<Segment> toDelete;

	dfs(0, visited, toDelete);

	sort(toDelete.begin(), toDelete.end());
	int barriersIndex = 0;

	for (auto &seg : toDelete)
	{
		while (not (this->_barriers[barriersIndex] == seg))
		{
			barriersIndex++;
		}
		this->_barriers.erase(this->_barriers.begin() + barriersIndex);
	}

	for (Segment &seg : this->_barriers)
	{
		seg.scale(float(STEP));
	}
}

void Labirinth::dfs(int vertex, std::vector<bool> &visited, std::vector<Segment> &toDelete)
{
	visited[vertex] = true;

	int targetVertex;

	int x = getSquareX(vertex);
	int y = getSquareY(vertex);

	std::vector<int> visitOrder = { 0, 1, 2, 3 };
	Util::permute(visitOrder);

	for (int i = 0; i < 4; i++)
	{
		int nx = x + _dx[visitOrder[i]];
		int ny = y + _dy[visitOrder[i]];
		int targetId = getSquareId(nx, ny);
		
		if (validatePosition(nx, ny) and !visited[targetId])
		{
			Point origin(x, y);
			Point target(nx, ny);
			if (target < origin)
			{
				std::swap(origin, target);
			}
			bool verticalMove = visitOrder[i] > 1;
			Segment seg;
			Point segOrigin = target;
			Point segTarget = target;
			if (verticalMove)
			{
				segTarget.setX(segTarget.getX() + 1);
			}
			else
			{
				segTarget.setY(segTarget.getY() + 1);
			}
			seg = Segment(segOrigin, segTarget);

			toDelete.push_back(seg);
			dfs(targetId, visited, toDelete);
		}
	}
}

const int Labirinth::getSquareId(const int x, const int y)
{
	return x + y * this->_hSize;
}

const int Labirinth::getSquareX(const int id)
{
	return id % this->_hSize;
}

const int Labirinth::getSquareY(const int id)
{
	return id / this->_hSize;
}

const bool Labirinth::validatePosition(const int x, const int y)
{
	return x >= 0 and y >= 0 and x < _hSize and y < _vSize;
}

bool Labirinth::victory(const Point position) const
{
	return	position.getX() - globals::SCREEN_WIDTH + STEP > 0 and
					position.getY() - globals::SCREEN_HEIGHT + STEP > 0;
}