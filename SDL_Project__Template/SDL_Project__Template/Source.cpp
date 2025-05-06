#include <SDL.h>
#include <iostream>


#include "GameLoop.h"

int main(int argc, char* argv[])
{
	GameLoop* game = new GameLoop;

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