#ifndef BALL_HPP
#define BALL_HPP

#include "sprite.hpp"
#include "segment.hpp"

#include <vector>

class Ball
{
public:

	Ball();
	~Ball();

	Ball(Graphics &graphics, float x, float y);

	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();

	void draw(Graphics &graphics);
	void update();
	void collisionCheck(std::vector<Segment> segments);

	float getX() { return this->_x; }
	float getY() { return this->_y; }

private:

	Sprite *_sprite;
	float _x, _y;
	float _diameter;

	void handleBorderCollision();
	void handleSegmentCollision(Segment segment);

};

#endif