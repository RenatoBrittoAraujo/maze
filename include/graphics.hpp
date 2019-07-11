#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include "color.hpp"

#include <SDL2/SDL.h>
#include <map>
#include <string>

class Graphics
{
public:
	Graphics(const char * windowTitle);
	~Graphics();

	SDL_Surface *loadImage(const std::string &path);

	void blitSurface(SDL_Texture *source, SDL_Rect *sourceRectagle, SDL_Rect *destinationRectangle);

	void flip();

	void fillBackground();

	SDL_Renderer *getRenderer() const;

	void setRenderColor(Color color);

	void destroy();

private:

	SDL_Window *_window;
	SDL_Renderer *_renderer;

	std::map<std::string, SDL_Surface *> _spriteSheets;
};

#endif