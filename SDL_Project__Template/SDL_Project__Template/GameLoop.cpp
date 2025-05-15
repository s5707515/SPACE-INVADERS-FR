#include <SDL.h>
#include <iostream>

#include "GameLoop.h"
#include "Player.h"
#include "GameManager.h" //Enemy.h and Projectile.h are included in this

#include <vector>
GameLoop::GameLoop(int _SCREEN_WIDTH, int _SCREEN_HEIGHT) //CTOR (Automatically initialise the game)
{
	SCREEN_WIDTH = _SCREEN_WIDTH;
	SCREEN_HEIGHT = _SCREEN_HEIGHT;

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

	GameManager gameManager(SCREEN_WIDTH, SCREEN_HEIGHT);

	GameManager* gmPtr{ nullptr };

	gmPtr = &gameManager;

	Player* player = new Player(renderer, (char*)"SpaceShip.bmp", 100, SCREEN_HEIGHT - 100, 80, 80, gmPtr, 3);

	//CREATE VECTORS TO HOLD MULTIPLE OBJECTS

	std::vector<Enemy*> enemies;
	std::vector<Projectile*> projectiles;



	float enemyTimer = 0.0f;

	float enemySpawnRate = 2.5f;

	float enemyCooldown = 0.0f;

	float enemyFireRate = 5.0f; 

	

	


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

	
		//FRAME LIMITING

		while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksCount + 16)); //wait 16MS (60FBS)

		//Calc deltatime in seconds

		float deltaTime = (SDL_GetTicks() - ticksCount) / 1000.0f;

		//Update tick count for next frame

		ticksCount = SDL_GetTicks();

		//Clamp deltatime (prevent framedrops)

		if (deltaTime > 0.05f)
		{
			deltaTime = 0.05f;
		}





		//SPAWN ENEMIES

		if (enemyTimer >= enemySpawnRate)
		{
			gameManager.CreateEnemy(renderer, enemies);

			enemyTimer -= enemySpawnRate;
		}
		else
		{
			enemyTimer += deltaTime;
		}

		//SPAWN ENEMY PROJECTILE

		if (enemies.size() != 0)
		{
			if (enemyCooldown > enemyFireRate)
			{
				int randEnemy = rand() % enemies.size();

				SDL_Rect position = enemies[randEnemy]->GetPosition();

				SDL_Point spawnPos{ position.x + (position.w / 2), position.y + (position.h / 2)};
				gameManager.CreateProjectile(renderer, projectiles, Projectile::Team::ENEMY_TEAM, spawnPos);

				enemyCooldown = 0;

				enemyFireRate = (rand() % 4) + 1;
				
			}
		}

		enemyCooldown += deltaTime;

		
		
		//MOVE SPRITES

		player->Move(deltaTime);


		//Let player shoot
		
		player->Shoot(projectiles, deltaTime);




		//UPDATE ENEMIES


		gameManager.UpdateEnemies(enemies, deltaTime);

		gameManager.UpdateProjectiles(projectiles, deltaTime);

		//MANAGE COLLISIONS:


		//Check if player collided with enemies

		for (int i = 0; i < enemies.size(); i++)
		{
			if (player->CheckCollision(enemies[i]->GetPosition()))
			{
				std::cout << "Enemy collided with player. " << std::endl;

				enemies.erase(enemies.begin() + i);

				player->health->TakeDamage(1);

				std::cout << "Player Health: " << player->health->GetCurrentHealth() << std::endl;

			}
		}

		//Check if player collided with enemy projectile

		for (int i = 0; i < projectiles.size(); i++)
		{
			if (projectiles[i]->CheckCollision(player->GetPosition()))
			{
				if (projectiles[i]->GetTeam() == Projectile::Team::ENEMY_TEAM)
				{
					//Damage Player

					player->health->TakeDamage(projectiles[i]->GetDamage());


					//Destroy projectile

					projectiles.erase(projectiles.begin() + i);

					std::cout << "Projectile collided with player" << std::endl;
				}
			}
		}


		//Check if projectiles collided with enemies

		for (int i = 0; i < enemies.size(); i++)
		{
			for (int j = 0; j < projectiles.size(); j++)
			{
				if (projectiles[j]->CheckCollision(enemies[i]->GetPosition())) //Check for collision
				{
					//CHECK WHICH TEAM THE PROJECTILE IS ON

					if (projectiles[j]->GetTeam() == Projectile::Team::PLAYER_TEAM)
					{

						//Damage Enemy

						enemies[i]->health->TakeDamage(projectiles[j]->GetDamage());

						//Destroy projectile

						projectiles.erase(projectiles.begin() + j);

						std::cout << "Projectile collided with enemy" << std::endl;

					}
				}
			}
		}

		//DESTROY DEAD ENEMIES (enemies cant be destroyed in nested loop as will cause range errors)

		for (int i = 0; i < enemies.size(); i++)
		{
			if (!enemies[i]->health->IsAlive())
			{
				enemies.erase(enemies.begin() + i);
			}
		}

		

		//Clear Old Render

		SDL_RenderClear(renderer);


		//DRAW SPRITES
		
		
		player->DrawSprite();
		

		

		for (unsigned int i = 0; i < enemies.size(); i++)
		{

			enemies[i]->DrawSprite();

		}

		for (unsigned int i = 0; i < projectiles.size(); i++)
		{

			projectiles[i]->DrawSprite();

		}


		//Present Render each Frame

		SDL_RenderPresent(renderer);

		//Check for quit

		if (!player->health->IsAlive())
		{
			quit = true;
		}
	}

	delete player;



}

