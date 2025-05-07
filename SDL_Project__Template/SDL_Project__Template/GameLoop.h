#pragma once

#include <sdl.h>

class GameLoop
{
private:

	//WINDOW DIMENSIONS

	int SCREEN_WIDTH = 600;

	int SCREEN_HEIGHT = 800;


	//SDL STUFF

	SDL_Window* window;
	SDL_Renderer* renderer;

	bool SetUpGame(); //set up SDL Window, Renderer
	void EndGame(); //Clean up SDL

public:

	GameLoop(int _SCREEN_WIDTH, int _SCREEN_HEIGHT); //CTOR
	~GameLoop(); //DTOR

	void PlayGame(); // Contains the actual gameloop

};