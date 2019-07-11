#include "game.hpp"
#include "logger.hpp"
#include "util.hpp"
#include "ball.hpp"
#include "input.hpp"
#include "labirinth.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

Game::Game()
{}

Game::~Game()
{}

bool Game::init(const char *title)
{
	int flags = 0;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		Logger::logError("Initalizing failure", "SDL Subsystems failed to initialize properly", SDL_GetError());
		return false;
	}

	if (_verbose)
	{
		Logger::logInfo("SDL Subsystems initialized");
	}

	_graphics = new Graphics("SDL game");

	// Standard background color set to white

	/* Custom class initialization */

	_graphics->loadImage("assets/circle.png");

	_player = new Ball(*this->_graphics, 100, 100);

	_labirinth = new Labirinth();

	/* End of class initialization */

	_isRunning = true;
	return true;
}

void Game::handleUserInput()
{
	if (SDL_PollEvent(&this->_event))
	{
		if (this->_event.type == SDL_QUIT)
		{
			exit();
		}
		else if (this->_event.type == SDL_KEYDOWN)
		{
			if (this->_event.key.repeat == 0)
				this->_input.keyDownEvent(this->_event);
		}
		else if (this->_event.type == SDL_KEYUP)
		{
			this->_input.keyUpEvent(this->_event);
		}
	}

	if (this->_input.wasKeyPressed(SDL_SCANCODE_ESCAPE))
	{
		exit();
	}

	if (this->_input.isKeyHeld(SDL_SCANCODE_A))
	{
		this->_player->moveLeft();
	}
	if (this->_input.isKeyHeld(SDL_SCANCODE_D))
	{
		this->_player->moveRight();
	}
	if (this->_input.isKeyHeld(SDL_SCANCODE_W))
	{
		this->_player->moveUp();
	}
	if (this->_input.isKeyHeld(SDL_SCANCODE_S))
	{
		this->_player->moveDown();
	}

	if (this->_input.isKeyHeld(SDL_SCANCODE_R))
	{
		_backgroundColor = Color(
			Util::randInt(180, 255),
			Util::randInt(180, 255),
			Util::randInt(180, 255),
			255
		);
	}
}

void Game::update()
{
	/* Updating of game classes */

	this->handleCollisions();
	this->_player->update();

	/* End of updating */
}

void Game::render()
{
	_graphics->setRenderColor(_backgroundColor);
	_graphics->fillBackground();

	/* Rendering of different classes */

	_graphics->setRenderColor(_segmentColor);
	_labirinth->draw(*this->_graphics);

	_player->draw(*this->_graphics);

	/* End of rendering */
	
	_graphics->flip();
}

void Game::exit()
{
	_isRunning = false;
	SDL_Quit();
}

bool Game::running()
{
	return _isRunning;
}

void Game::run()
{
	unsigned int last = SDL_GetTicks();
	unsigned int current;

	while (this->running())
	{
		current = SDL_GetTicks();

		this->handleUserInput();
		this->update();

		if(current - last >= (1000 / _framerate))
		{
			this->render();
			last = current;
		}

		SDL_Delay(10);
	}
}

// Getters and Setters

void Game::setFramerate(int framerate)
{
	this->_framerate = framerate;
}

void Game::setVerbose(bool verbose)
{
	this->_verbose = verbose;
}

void Game::handleCollisions()
{
	auto barriers = this->_labirinth->getBarriers();
	this->_player->collisionCheck(barriers);
}