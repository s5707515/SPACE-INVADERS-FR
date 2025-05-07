#include <SDL.h>
#include <iostream>

#include "time.h"
#include "GameLoop.h"

int main(int argc, char* argv[])
{

	//WINDOW DIMENSIONS

	int SCREEN_WIDTH = 600;

	int SCREEN_HEIGHT = 800;



	srand(time(0));

	GameLoop* game = new GameLoop(SCREEN_WIDTH,SCREEN_HEIGHT);

	if (game != nullptr)
	{
		game->PlayGame(); //Play the game loop

		delete game;
	}
	else
	{
		std::cout << "Failed to play the gameloop..." << std::endl;
	}

	return 0;
}