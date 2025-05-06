#pragma once

#include <sdl.h>

class GameLoop
{
private:

	//WINDOW DIMENSIONS

	int SCREEN_WIDTH = 1080;

	int SCREEN_HEIGHT = 720;

	//SDL STUFF

	SDL_Window* window;
	SDL_Renderer* renderer;

	bool SetUpGame(); //set up SDL Window, Renderer
	void EndGame(); //Clean up SDL

public:

	GameLoop(); //CTOR
	~GameLoop(); //DTOR

	void PlayGame(); // Contains the actual gameloop

};