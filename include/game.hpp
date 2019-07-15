#ifndef GAME_HPP
#define GAME_HPP

#include "graphics.hpp"
#include "ball.hpp"
#include "input.hpp"
#include "labirinth.hpp"
#include "color.hpp"

struct SDL_Window;
struct SDL_Renderer;
class Player;

class Game
{
public:
	Game();
	~Game();

	/*
		Initizes game's window, renderer, and loads textures to GPU
		params:
			title: window name
			xpos: x position window will be initilized in from 0x axis of screen
			ypos: y position window will be initilized in from 0y axis of screen
			width: screen width
			height: screen height
			fullscreen: true if window will ocuppy all screen
		returns false if game has not been initialized correctly
		Log error to stdout
	 */
	bool init(const char *title);

	/*
		Destroy current renderer and render, unload textures from GPU
	 */
	void exit();

	/*
		Returns true if game is currently running
	 */
	bool running();

	/*
		Runs main game loop
	 */
	void run();

	// Setters and Getters

	void setVerbose(bool verbose);
	void setFramerate(int framerate);

private:

	/*
		Configure starting game conditions such as spawn point and labirinth
	 */
	void startGame();

	/*
		Hanles user input as SDL's events
	*/
	void handleUserInput();

	/*
		Update all game objects
	 */
	void update();
	
	/*
		Render all game objects to screen
	 */
	void render();

	/*
		Process collisions between game objects
	 */
	void handleCollisions();

			bool _verbose;
	int _framerate;

	Ball *_player;
	Labirinth *_labirinth;

	bool _isRunning;
	Graphics *_graphics;
	Input _input;

	SDL_Event _event;

	Color _segmentColor = Color(140, 140, 140, 255);
	Color _backgroundColor = Color(200, 200, 230, 255);

};

#endif