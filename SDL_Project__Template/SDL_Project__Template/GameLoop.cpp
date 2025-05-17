#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>



#include <string>

#include "GameLoop.h"

#include "Player.h"
#include "GameManager.h" //Enemy.h and Projectile.h are included in this
#include "UI.h"

#include "Boss.h"

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


	//INITIALISE TTF

	if (TTF_Init() < 0)
	{
		std::cout << "SDL_ttf could not be initialised! SDL Error: " << SDL_GetError() << std::endl;

		system("pause");
		success = false;
	}
	else  
	{
		font = TTF_OpenFont("PixelifySans-Bold.ttf", 50);

		if (!font)
		{
			std::cout << "Failed to load font: " << SDL_GetError() << std::endl;
		}
	}

	return success;
}

void GameLoop::EndGame()
{

	//CLOSE FONTS

	TTF_CloseFont(font);

	//DESTROY RENDERER

	SDL_DestroyRenderer(renderer);

	//DESTROY WINDOW

	SDL_DestroyWindow(window);

	//QUIT SDL LIBRARIES

	TTF_Quit();

	SDL_Quit();

	std::cout << "Game was clean up successfully!" << std::endl;
}

void GameLoop::PlayGame() //The Actual GameLoop of the game
{
	SDL_Event event;

	bool quit = false;

	phase = REGULAR_WAVE;



	GameManager gameManager(SCREEN_WIDTH, SCREEN_HEIGHT);

	GameManager* gmPtr{ nullptr };

	gmPtr = &gameManager;

	Player* player = new Player(renderer, (char*)"SpaceShip.bmp", 100, SCREEN_HEIGHT - 100, 80, 80, gmPtr, 3);

	//CREATE VECTORS TO HOLD MULTIPLE OBJECTS

	std::vector<Enemy*> enemies;
	std::vector<Projectile*> projectiles;
	std::vector<Boss*> bosses; //(Theres only ever one)

	//CREATE TEXTBOXS
	
	SDL_Color white = { 255,255,255 };

	SDL_Color red = { 255, 0, 0 };

	SDL_Rect healthTextPos{10, 75, 0, 0};
	TextBox* healthText = new TextBox(font, (char*)"Health: 0", red, healthTextPos, renderer);

	SDL_Rect scoreTextPos{10, 10, 0, 0 };
	TextBox* scoreText = new TextBox(font, (char*)"Score: 0", white, scoreTextPos, renderer);


	SDL_Rect enemiesLeftPos{ SCREEN_WIDTH - 400, 75, 0, 0 };
	TextBox* enemiesText = new TextBox(font, (char*)"Enemies Left: 0", white, enemiesLeftPos, renderer);


	SDL_Rect waveTextPos{ SCREEN_WIDTH - 300, 10, 0, 0 };
	TextBox* waveText = new TextBox(font, (char*)"Wave: 0", white, waveTextPos, renderer);

	//CREATE WAVES 

	Wave* wave1 = new Wave(1, 7, 3.5);
	Wave* wave2 = new Wave(2, 9, 2.5);
	Wave* wave3 = new Wave(3, 12, 2);
	Wave* wave4 = new Wave(4, 16, 1.5);


	//Wave* tempWave = new Wave(69, 1, 2);


	std::vector<Wave*> waves = { wave1, wave2, wave3, wave4 };
	//std::vector<Wave*> waves{tempWave}; //TEMPORARY

	int wavePointer = 0;


	float enemyTimer = 0.0f;

	float enemySpawnRate = waves[0]->GetSpawnFrequency();


	float bossAttackTimer = 3.0f;

	float bossCooldown = 0;

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


	

		if (phase == REGULAR_WAVE) 	//STUFF WE DONT WANT TO HAPPEN DURING A BOSS WAVE
		{

			//CHECK IF NEW WAVE

			if (waves[wavePointer]->GetWaveEnd())
			{
				if (wavePointer == waves.size() - 1)
				{

					//Initiate boss wave after enemy waves

					phase = BOSS_WAVE;

					bosses.push_back(new Boss(renderer, (char*)"UFO.bmp", (SCREEN_WIDTH / 2) - 360, -180, 720, 280, 1.5, 75, &gameManager));

					bossAttackTimer = bosses[0]->GetAttackRate();


				}
				else
				{
					wavePointer++;

					enemySpawnRate = waves[wavePointer]->GetSpawnFrequency();

					std::cout << "NEW WAVE INITIATED:" << std::endl;

					enemyTimer = 0;
				}
			}


			//SPAWN ENEMIES

			if (enemyTimer >= enemySpawnRate)
			{
				if ((waves[wavePointer]->GetNumberOfEnemiesLeft() - waves[wavePointer]->GetNumberOfEnemiesAlive()) > 0)
				{
					gameManager.CreateEnemy(renderer, enemies, waves[wavePointer]);


				}
				enemyTimer -= enemySpawnRate;

			}
			else
			{
				enemyTimer += deltaTime;
			}
		}


	

		if (phase == BOSS_WAVE)
		{
			bossCooldown += deltaTime;

			if (bossCooldown > bossAttackTimer)
			{
				int attackID = (rand() % 4) + 1;


				if (attackID == 1) //Spawn enemies 25% of the time
				{
					enemyCooldown = 0; //Reset cooldown so they don't fire before player can react

					bosses[0]->BackUpCall(enemies, 2);

				}
				else //Fire projectiles 75% of the time
				{
					bosses[0]->FireBarrage(projectiles, 5);
				}

				
				bossCooldown = 0;
			}




			//BOSS COLLISIONS

			//Check if boss collided with player projectile

			for (int j = 0; j < bosses.size(); j++)
			{
				for (int i = 0; i < projectiles.size(); i++)
				{
					if (projectiles[i]->CheckCollision(bosses[j]->GetPosition()))
					{
						if (projectiles[i]->GetTeam() == Projectile::Team::PLAYER_TEAM)
						{
							//Damage Player

							bosses[j]->health->TakeDamage(projectiles[i]->GetDamage());


							//Destroy projectile

							delete projectiles[i];
							projectiles.erase(projectiles.begin() + i);
							i--;
							std::cout << "Projectile collided with boss" << std::endl;
						}
					}
				}
			}

			//CHECK IF BOSS HAS BEEN DEFEATED

			for (int i = 0; i < bosses.size(); i++)
			{
				if (!bosses[i]->health->IsAlive())
				{
					delete bosses[i]; //free up space
					bosses.erase(bosses.begin() + i); //remove index
					i--;
					//Add score

					gameManager.IncrementScore(300);

					phase = VICTORY;
				}
			}


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

		for (int i = 0; i < bosses.size(); i++) //MOVE BOSS
		{
			bosses[i]->MoveBoss(deltaTime);

			if (bosses[i]->GetY() > SCREEN_HEIGHT)
			{
				delete bosses[i];
				bosses.erase(bosses.begin() + i);
				i--;
			}
		}


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

				delete enemies[i];
				enemies.erase(enemies.begin() + i);
				i--;

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

					delete projectiles[i];
					projectiles.erase(projectiles.begin() + i);
					i--;
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

						delete projectiles[j];
						projectiles.erase(projectiles.begin() + j);
						j--;

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
				delete enemies[i]; //free up space
				enemies.erase(enemies.begin() + i); //remove index
				i--;
				//Add score

				gameManager.IncrementScore(10);
			}
		}


		

		//UPDATE TEXTBOXES

	
		std::string healthTxt = "Health: " + std::to_string(player->health->GetCurrentHealth());
		healthText->ChangeText((char*)healthTxt.c_str());


		std::string scoreTxt = "Score: " + std::to_string(gameManager.GetScore());
		scoreText->ChangeText((char*)scoreTxt.c_str());

		std::string enemiesTxt = "Enemies Left: " + std::to_string(waves[wavePointer]->GetNumberOfEnemiesLeft());
		enemiesText->ChangeText((char*)enemiesTxt.c_str());

		if (phase == REGULAR_WAVE)
		{
			std::string waveTxt = "Wave: " + std::to_string(waves[wavePointer]->GetWaveNum());
			waveText->ChangeText((char*)waveTxt.c_str());

		}
		else if (phase == BOSS_WAVE)
		{

			std::string waveTxt = "Wave: BOSS";
			waveText->ChangeText((char*)waveTxt.c_str());

		}

		


		//Clear Old Render

		SDL_RenderClear(renderer);


		//DRAW SPRITES
		
		
		player->DrawSprite();

		for (unsigned int i = 0; i < bosses.size(); i++)
		{
			bosses[i]->DrawSprite();
		}

	
		

		for (unsigned int i = 0; i < enemies.size(); i++)
		{

			enemies[i]->DrawSprite();

		}

		for (unsigned int i = 0; i < projectiles.size(); i++)
		{

			projectiles[i]->DrawSprite();

		}

		//DRAW TEXT

		healthText->DrawText();
		scoreText->DrawText();
		enemiesText->DrawText();
		waveText->DrawText();


		//Present Render each Frame

		SDL_RenderPresent(renderer);

		//Check for quit

		if (!player->health->IsAlive())
		{
			quit = true;
		}
	}

	//Delete TextBoxes

	for (int i = 0; i < waves.size(); i++)
	{
		delete waves[i];
	}


	delete player;



}

