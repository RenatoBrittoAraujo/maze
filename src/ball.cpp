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
	this->_sprite = new Sprite(graphics, "assets/circle.png", 0, 0, 112, 112);
	this->_diameter = floor(Util::applyScale(float(112)));
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

// Credits for the code:
// https://github.com/edsomjr/TEP/blob/master/Geometria_Computacional/slides/CC-2/CC-2.pdf
// Valeu Edson!
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

	/*
	Point center(_x, _y);
	float distFirst = segment.getFirst().euclidianDistance(center);
	float distSecond = segment.getSecond().euclidianDistance(center);

	if (distFirst < _radius)
	{
		Point vector(fx - _x, fy - _y);
		vector = vector * (- (_radius - distFirst) / distFirst);
		_x += vector.getX();
		_y += vector.getY();
	}

	if (distSecond < _radius)
	{
		Point vector(fx - _x, fy - _y);
		vector = vector * (-(_radius - distSecond) / distSecond);
		_x += vector.getX();
		_y += vector.getY();
	}
 	*/

	/*
	Point P = segment.getFirst();
	Point Q = segment.getSecond();
	
	float a = pow(Q.getX() - P.getX(), 2.0) + pow(Q.getY() - P.getY(), 2.0);

	float b = 2.0f * ( (Q.getX() - P.getX()) * (P.getX() - this->_x) 
		+ (Q.getY() - P.getY()) * (P.getY() - this->_y));

	float d = pow(this->_x, 2.0) + pow(this->_y, 2.0) + pow(P.getX(), 2.0)
		+ pow(P.getY(), 2.0) + 2.0f * (this->_x * P.getX() + this->_y * P.getY());

	float D = b * b - 4 * a * d;

	if(D < 1e-6)
	{
		return;
	}

	float u = (-b + sqrt(D)) / (2.0f * a);
	float x = P.getX() + u * (Q.getX() - P.getX());
	float y = P.getY() + u * (Q.getY() - P.getY());

	Point P1(x, y);

	u = (-b - sqrt(D)) / (2.0f * a);
	x = P.getX() + u * (Q.getX() - P.getX());
	y = P.getY() + u * (Q.getY() - P.getY());

	Point P2(x, y);

	float dist = P1.euclidianDistance(P2);
	float h = sqrt(dist / (4.0f * this->_radius));
	float magnitude = this->_radius - h;
	
	if(magnitude < 0.0f)
	{
		return;
	}

	std::cout<<"CORRECTING COLLISION"<<std::endl;

	float correction = -(this->_radius - h) / this->_radius;

	float cX = (P1.getX() + P2.getX()) / 2.0f;
	float cY = (P1.getY() + P2.getY()) / 2.0f;

	Point vector((this->_x - cX) * correction, (this->_y - cY) * correction);

	this->_x += vector.getX();
	this->_y += vector.getY();
	*/
}