#pragma once

#include <sdl.h>
#include <SDL_ttf.h>

#include "Sounds.h"

enum Phase
{
	REGULAR_WAVE,

	BOSS_WAVE,

	GAME_OVER,

	WAIT_TIME

};

enum MenuState
{
	MAIN_MENU,

	INSTRUCTIONS
};

class GameLoop
{
private:

	//WINDOW DIMENSIONS

	int SCREEN_WIDTH = 600;

	int SCREEN_HEIGHT = 800;

	bool closeGame = false;


	//SDL STUFF

	SDL_Window* window;
	SDL_Renderer* renderer;

	bool SetUpGame(); //set up SDL Window, Renderer
	void EndGame(); //Clean up SDL


	//TIME

	Uint32 ticksCount;

	float deltaTime;

	//TEXT TTF STUFF

	TTF_Font* font{ nullptr };

	TTF_Font* bigFont{ nullptr };

	TTF_Font* smallFont{ nullptr };

	SDL_Color white = { 255,255,255 };

	SDL_Color red = { 255, 0, 0 };

	SDL_Color yellow = { 255, 255, 0 };

	SDL_Color black = { 0,0,0 };


	//MUSIC STUFF

	Music* menuMusic{ nullptr };

	Music* wavesMusic{ nullptr };

	Music* wavesMusic2{ nullptr };

	Music* bossMusic{ nullptr };


	SFX* menu1{ nullptr };
	SFX* menu2{ nullptr };


	SFX* deathSFX{ nullptr };

	SFX* enemyLazer1{ nullptr };
	SFX* enemyLazer2{ nullptr };

	SFX* bossWarningSFX{ nullptr };
	SFX* backUpCallSFX{ nullptr };
	SFX* bossDeathSFX{ nullptr };
	
	SFX* enemyDeath1{ nullptr };
	SFX* enemyDeath2{ nullptr };
	SFX* enemyDeath3{ nullptr };

	SFX* playerDamage{ nullptr };

	//PHASE

	Phase phase;

	MenuState menuState;

	





public:

	GameLoop(int _SCREEN_WIDTH, int _SCREEN_HEIGHT); //CTOR
	~GameLoop(); //DTOR

	void PlayGame(); // Contains the actual gameloop

	void DoFrameLimiting();//Does frame limiting and returns deltaTime between frames.


	void MainMenu(); //Contains the Main Menu loop (Returns true for PlayGame() and false for quit)

	bool GetCloseGame() { return closeGame; }
};