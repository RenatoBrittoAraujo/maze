#ifndef BALL_HPP
#define BALL_HPP

#include "sprite.hpp"
#include "segment.hpp"
#include "point.hpp"

#include <vector>

class Ball
{
public:

	Ball();
	~Ball();

	Ball(Graphics &graphics);

	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();

	void draw(Graphics &graphics);
	void update();
	void collisionCheck(std::vector<Segment> segments);

	float getX() { return this->_x; }
	float getY() { return this->_y; }

	void setPosition(const Point position) { 
		this->_x = position.getX(); this->_y = position.getY(); }

	Point getPosition() const;

private:

	Sprite *_sprite;
	float _x, _y;
	float _diameter;

	void handleBorderCollision();
	void handleSegmentCollision(Segment segment);

};

#endif