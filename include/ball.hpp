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

private:

	Sprite *_sprite;
	float _x, _y;
	float _radius;

	void handleBorderCollision();
	void handleSegmentCollision(Segment segment);

};

#endif