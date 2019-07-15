#include "ball.hpp"
#include "graphics.hpp"
#include "sprite.hpp"
#include "globals.hpp"
#include "util.hpp"

#include <algorithm>

namespace 
{
	const float ballSpeed = 5.0; 
}

Ball::Ball()
{}

Ball::~Ball()
{}

Ball::Ball(Graphics &graphics)
{
	const int imageSize = 112;
	this->_sprite = new Sprite(graphics, "assets/circle.png", 0, 0, imageSize, imageSize);
	this->_diameter = floor(Util::applyScale(float(imageSize)));
}

void Ball::draw(Graphics &graphics)
{
	this->_sprite->draw(graphics, this->_x, this->_y);
}

void Ball::update()
{

}

void Ball::moveDown()
{
	this->_y += ballSpeed;
}

void Ball::moveUp()
{
	this->_y -= ballSpeed;
}

void Ball::moveLeft()
{
	this->_x -= ballSpeed;
}

void Ball::moveRight()
{
	this->_x += ballSpeed;
}

void Ball::collisionCheck(std::vector<Segment> barriers)
{
	// this->handleBorderCollision();
	for (auto segment : barriers)
	{

		this->handleSegmentCollision(segment);
	}
}

Point Ball::getPosition() const
{
	return Point(this->_x, this->_y);
}

void Ball::handleBorderCollision()
{
	if (_x < 0)
		_x = 0;
	if (_x + _diameter > globals::SCREEN_WIDTH)
		_x = globals::SCREEN_WIDTH - _diameter;
	if (_y < 0)
		_y = 0;
	if (_y + _diameter > globals::SCREEN_HEIGHT)
		_y = globals::SCREEN_HEIGHT - _diameter;
}

void Ball::handleSegmentCollision(Segment segment)
{
	const float fx = segment.getFirst().getX();
	const float fy = segment.getFirst().getY();
	const float sx = segment.getSecond().getX();
	const float sy = segment.getSecond().getY();

	float x = _x + _diameter / 2.0f;
	float y = _y + _diameter / 2.0f;
	float radius = _diameter / 2.0f;

	if (Util::fequals(fx, sx))
	{
		float segx = fx;
		if (segx >= x - radius and segx <= x + radius and
				std::min(fy, sy) < y + radius and std::max(fy, sy) > y - radius)
		{
			if(segx - (x - radius) > x + radius - segx)
			{
				x = segx - radius - 1;
			}
			else
			{
				x = segx + radius + 1;
			}
		}	
	} 
	else 
	{
		float segy = fy;
		if (segy >= y - radius and segy <= y + radius and
				std::min(fx, sx) < x + radius and std::max(fx, sx) > x - radius)
		{
			if (segy - (y - radius) > y + radius - segy)
			{
				y = segy - radius - 1;
			}
			else
			{
				y = segy + radius + 1;
			}
		}
	}

	_x = x - radius;
	_y = y - radius;
}