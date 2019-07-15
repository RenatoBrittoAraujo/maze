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

	/*
		Changes the ball position
	 */
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();

	/*
		Draws ball to renderer
	 */
	void draw(Graphics &graphics);

	/*
		Updates ball's parameters
	 */
	void update();

	/*
		Checks if balls is colliding with some segment of segments
	 */
	void collisionCheck(std::vector<Segment> segments);

	float getX() { return this->_x; }
	float getY() { return this->_y; }

	void setPosition(const Point position) { 
		this->_x = position.getX(); this->_y = position.getY();
	}

	Point getPosition() const;

private:

	Sprite *_sprite;
	float _x, _y;
	float _diameter;

	/*
		Handles collisions with screen
	 */
	void handleBorderCollision();

	/*
		Handles collisions with a specific segment
	 */
	void handleSegmentCollision(Segment segment);

};

#endif