#include "game.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

int main(int argc, char **argv)
{
	bool verbose = false;
	int framerate = 60;

	if(argc > 1)
	{
		verbose = (argv[1][1] == 'v');
	}

	if (argc > 2)
	{
		framerate = atoi(argv[2]);
	}

	Game game;

	game.setFramerate(framerate);
	game.setVerbose(verbose);

	bool correctInitialization = game.init("2D Engine");

	if (correctInitialization)
	{
		// Main game loop running
		game.run();
	}

	game.exit();

	return 0;
}