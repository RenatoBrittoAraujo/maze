#include "ball.hpp"
#include "graphics.hpp"
#include "sprite.hpp"
#include "globals.hpp"

namespace 
{
	const double ballSpeed = 5.0; 
}

Ball::Ball()
{}

Ball::~Ball()
{}

Ball::Ball(Graphics &graphics, float x, float y) :
	_x(x), _y(y)
{
	this->_sprite = new Sprite(graphics, "assets/circle.png", 0, 0, 112, 112);
	this->_radius = (float(112) / 2.0f) * globals::SCALE;
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

#include <iostream>

void Ball::collisionCheck(std::vector<Segment> barriers)
{
	this->handleBorderCollision();
	for(auto segment : barriers)
	{

		this->handleSegmentCollision(segment);
	}
}

void Ball::handleBorderCollision()
{
	if(_x < 0)
		_x = 0;
	if(_x + (int)((double)112 * globals::SCALE) > globals::SCREEN_WIDTH)
		_x = globals::SCREEN_WIDTH - (int)((double)112 * globals::SCALE);
	if (_y < 0)
		_y = 0;
	if (_y + (int)((double)112 * globals::SCALE) > globals::SCREEN_HEIGHT)
		_y = globals::SCREEN_HEIGHT - (int)((double)112 * globals::SCALE);
}

// Credits for most of the following competitive programming repo (in brazilian portuguese):
// https://github.com/edsomjr/TEP/blob/master/Geometria_Computacional/slides/CC-2/CC-2.pdf
// Valeu Edson!

// This routine finds the 2 intersection points from the line defined by segment
// and the circle defined by ball.
// Then checks if those two points are inside the segment (otherwise there is no collision)
// and creates a vector going the opposite direction from the collision center
// and updates the _x and _y of ball based on that vector
void Ball::handleSegmentCollision(Segment segment)
{
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
}