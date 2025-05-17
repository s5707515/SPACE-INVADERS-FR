#pragma once

#include <sdl.h>
#include <SDL_ttf.h>#

enum Phase
{
	REGULAR_WAVE,

	BOSS_WAVE,

	GAME_OVER

};

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


	//TIME

	Uint32 ticksCount;

	//TEXT TTF STUFF

	TTF_Font* font{ nullptr };

	//PHASE

	Phase phase;

	bool victory = false;



public:

	GameLoop(int _SCREEN_WIDTH, int _SCREEN_HEIGHT); //CTOR
	~GameLoop(); //DTOR

	void PlayGame(); // Contains the actual gameloop

};