#include <SDL.h>
#include <iostream>

#include "GameLoop.h"
#include "Player.h"

GameLoop::GameLoop() //CTOR (Automatically initialise the game)
{
	SetUpGame();
}

GameLoop::~GameLoop() //DTOR (Clean up memory)
{
	EndGame();
}

bool GameLoop::SetUpGame()
{
	bool success = true;

	//INITIALISE SDL

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "SDL could not initialize! SDL_Error:" << SDL_GetError() << std::endl;

		system("pause");
		success = false;
	}
	else
	{
		//CREATE WINDOW

		window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if (window == NULL)
		{
			std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;

			system("pause");
			success = false;
		}
		else
		{
			//CREATE RENDERER

			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);


			if (renderer == NULL)
			{
				std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;

				system("pause");
				success = false;
			}


		}
	}

	return success;
}

void GameLoop::EndGame()
{
	//DESTROY RENDERER

	SDL_DestroyRenderer(renderer);

	//DESTROY WINDOW

	SDL_DestroyWindow(window);

	//QUIT SDL LIBRARY

	SDL_Quit();

	std::cout << "Game was clean up successfully!" << std::endl;
}

void GameLoop::PlayGame() //The Actual GameLoop of the game
{
	SDL_Event event;

	bool quit = false;

	Player* player = new Player(renderer, (char*)"SpaceShip.bmp", 100, 650, 80, 80);

	while (!quit)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:

				quit = true;
				break;

			default:

				break;
			}
		}

		//FRAME BY FRAME STUFF

		//Clear Old Render

		SDL_RenderClear(renderer);

		//MOVE SPRITES

		player->Move();



		//DRAW SPRITES

		player->DrawSprite();

		//Present Render each Frame

		SDL_RenderPresent(renderer);
	}

	delete player;



}
