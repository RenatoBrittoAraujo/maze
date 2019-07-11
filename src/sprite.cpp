#include "sprite.hpp"
#include "globals.hpp"
#include "graphics.hpp"

#include <iostream>
#include <algorithm>

Sprite::Sprite() 
{}

Sprite::~Sprite() 
{}

Sprite::Sprite(Graphics &graphics, const std::string &path, int sourceX, int sourceY, int width, int height)
{
	this->_sourceRect.x = sourceX;
	this->_sourceRect.y = sourceY;
	this->_sourceRect.w = width;
	this->_sourceRect.h = height;

	this->_spriteSheet = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(path));
	if (_spriteSheet == NULL)
	{
		throw "Failed at creating surface texture from path | Class: Sprite";
	}
}

void Sprite::draw(Graphics &graphics, int x, int y)
{
	SDL_Rect destination = {x, y, (int)((float)this->_sourceRect.w * globals::SCALE), (int)((float)this->_sourceRect.h * globals::SCALE)};
	graphics.blitSurface(this->_spriteSheet, &this->_sourceRect, &destination);
}

void Sprite::update()
{

}