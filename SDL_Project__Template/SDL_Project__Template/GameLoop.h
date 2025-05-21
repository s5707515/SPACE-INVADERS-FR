#pragma once

#include <sdl.h>
#include <SDL_ttf.h>

#include "Sounds.h"

enum Phase //The 4 phases of the game
{
	REGULAR_WAVE,

	BOSS_WAVE,

	GAME_OVER,

	WAIT_TIME

};

enum MenuState //The 2 states that the menu can be in
{
	MAIN_MENU,

	INSTRUCTIONS
};

class GameLoop //Class used to cycle through the game, frame by frame
{
private:

	//WINDOW DIMENSIONS

	int SCREEN_WIDTH = 600;

	int SCREEN_HEIGHT = 800;

	bool closeGame = false; //Checks whether to quit the game completely (Ends program when true)


	//SDL STUFF

	SDL_Window* window;
	SDL_Renderer* renderer;

	bool SetUpGame(); //set up SDL Window, Renderer
	void EndGame(); //Clean up SDL


	//TIME

	Uint32 ticksCount; //The current tick count

	float deltaTime; //The time since last frame, clamped to 0.05

	//TEXT TTF STUFF (fonts and colours)

	TTF_Font* font{ nullptr };

	TTF_Font* bigFont{ nullptr };

	TTF_Font* smallFont{ nullptr };

	SDL_Color white = { 255,255,255 };

	SDL_Color red = { 255, 0, 0 };

	SDL_Color yellow = { 255, 255, 0 };

	SDL_Color black = { 0,0,0 };


	//MUSIC STUFF (background music and SFXs)

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

	//Instances of enums.

	Phase phase; //The current phase of the game loop

	MenuState menuState; //The current state of the menu

	





public:

	GameLoop(int _SCREEN_WIDTH, int _SCREEN_HEIGHT); //CTOR
	~GameLoop(); //DTOR

	void PlayGame(); // Contains the actual gameloop

	void DoFrameLimiting();//Does frame limiting and returns deltaTime between frames.


	void MainMenu(); //Contains the Main Menu loop (Returns true for PlayGame() and false for quit)

	bool GetCloseGame() { return closeGame; }
};