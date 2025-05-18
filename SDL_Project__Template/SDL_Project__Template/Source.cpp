#include <SDL.h>
#include <iostream>

#include "time.h"
#include "GameLoop.h"

int main(int argc, char* argv[])
{

	//WINDOW DIMENSIONS

	int SCREEN_WIDTH = 800;

	int SCREEN_HEIGHT = 1000;

	bool quit = false;

	srand(time(0));

	GameLoop* game = new GameLoop(SCREEN_WIDTH,SCREEN_HEIGHT);

	if (game != nullptr)
	{
		do
		{
			game->MainMenu();
			
			quit = game->GetCloseGame();
		

			

			if (!quit)
			{
				game->PlayGame(); //Play the game loop
				quit = game->GetCloseGame();
			}

		} while (!quit);
		

		delete game;
	}
	else
	{
		std::cout << "Failed to play the gameloop..." << std::endl;
	}

	return 0;
}