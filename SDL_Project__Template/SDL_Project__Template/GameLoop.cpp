#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>



#include <string>

#include "GameLoop.h"

#include "Sprite.h"
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
	else  //INITIALISE FONTS
	{
		font = TTF_OpenFont("PixelifySans-Bold.ttf", 50);

		if (!font)
		{
			std::cout << "Failed to load font: " << SDL_GetError() << std::endl;
			success = false;
		}

		bigFont = TTF_OpenFont("PixelifySans-Bold.ttf", 96);

		if (!bigFont)
		{
			std::cout << "Failed to load font: " << SDL_GetError() << std::endl;
			success = false;
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

void GameLoop::DoFrameLimiting()
{
	//FRAME LIMITING

	while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksCount + 16)); //wait 16MS (60FBS)

	//Calc deltatime in seconds

	deltaTime = (SDL_GetTicks() - ticksCount) / 1000.0f;

	//Update tick count for next frame

	ticksCount = SDL_GetTicks();

	//Clamp deltatime (prevent framedrops)

	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}

}

void GameLoop :: MainMenu()
{
	bool leaveMenu = false;

	menuState = MAIN_MENU;

	SDL_Event event;

	//CREATE TEXTBOXES / IMAGES

	Sprite* shipImage = new Sprite(renderer, (char*)"SpaceShip.bmp", SCREEN_WIDTH / 2 - 160, 180, 320, 320);

	SDL_Rect titlePos = {45,10,0,0};
	TextBox* titleText = new TextBox(bigFont,(char*)"SPACE SHOOTER",white, titlePos, renderer);

	SDL_Rect playGamePos = { SCREEN_WIDTH / 2 - 130, 600, 0,0 };
	TextBox* playGameText = new TextBox(font, (char*)"PLAY GAME", white, playGamePos, renderer);

	SDL_Rect instrPos = { SCREEN_WIDTH / 2 - 167, 700, 0,0 };
	TextBox* instrText = new TextBox(font, (char*)"INSTRUCTIONS", white, instrPos, renderer);

	SDL_Rect quitPos = { SCREEN_WIDTH / 2 - 65, 800, 0,0 };
	TextBox* quitText = new TextBox(font, (char*)"QUIT", red, quitPos, renderer);


	while (!leaveMenu)
	{

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:

					leaveMenu = true;

					closeGame = true;

					break;

				case SDL_MOUSEBUTTONDOWN:

					if (menuState == MAIN_MENU)
					{
						//Check Main Menu buttons for mouse click

						int x = event.button.x;
						int y = event.button.y;

						SDL_Point mousePos = { x, y };

						SDL_Rect playRect = playGameText->GetPositionRect();
						SDL_Rect instrRect = instrText->GetPositionRect();
						SDL_Rect quitRect = quitText->GetPositionRect();
					

						if (SDL_PointInRect(&mousePos, &playRect))
						{
							//Play Game

							leaveMenu = true;

							closeGame = false;
							
						}

						if (SDL_PointInRect(&mousePos, &instrRect))
						{
							//Show Instructions

							menuState = INSTRUCTIONS;
						}

						if (SDL_PointInRect(&mousePos,&quitRect))
						{
							//Quit Game

							leaveMenu = true;

							closeGame = true;

						}
					}
					else if (menuState == INSTRUCTIONS)
					{
						//Check instruction buttons for mouse click
					}

					break;
			}
		}


		//DO FRAME LIMITING

		DoFrameLimiting(); //Calculates deltaTime

		//Clear Old Render

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);


		if (menuState == MAIN_MENU)
		{
			titleText->DrawText();
			playGameText->DrawText();
			instrText->DrawText();
			quitText->DrawText();

			shipImage->DrawSprite();
		}






		//Present Render each Frame

		SDL_RenderPresent(renderer);


	}

}

void GameLoop::PlayGame() //The Actual GameLoop of the game
{
	bool retry = true;

	while (retry)
	{
		SDL_Event event;

		bool quit = false;
		
		retry = false; //Default to quit

		phase = REGULAR_WAVE;



		GameManager gameManager(SCREEN_WIDTH, SCREEN_HEIGHT);

		GameManager* gmPtr{ nullptr };

		gmPtr = &gameManager;

		Player* player = new Player(renderer, (char*)"SpaceShip.bmp", SCREEN_WIDTH / 2 - 40, SCREEN_HEIGHT - 100, 80, 80, gmPtr, 5);

		//CREATE VECTORS TO HOLD MULTIPLE OBJECTS

		std::vector<Enemy*> enemies;
		std::vector<Projectile*> projectiles;
		std::vector<Boss*> bosses; //(Theres only ever one)

		//CREATE TEXTBOXS

		

		SDL_Rect healthTextPos{ 10, 75, 0, 0 };
		TextBox* healthText = new TextBox(font, (char*)"Health: 0", red, healthTextPos, renderer);

		SDL_Rect scoreTextPos{ 10, 10, 0, 0 };
		TextBox* scoreText = new TextBox(font, (char*)"Score: 0", white, scoreTextPos, renderer);


		SDL_Rect enemiesLeftPos{ SCREEN_WIDTH - 400, 10, 0, 0 };
		TextBox* enemiesText = new TextBox(font, (char*)"Enemies Left: 0", white, enemiesLeftPos, renderer);

		SDL_Rect waveWarningTxtPos{ SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 180, 0, 0 };

		TextBox* waveWarningText = new TextBox(font, (char*)"WAVE 1", yellow, waveWarningTxtPos, renderer);


		SDL_Rect GOScorePos = { SCREEN_WIDTH / 2 - 120, SCREEN_HEIGHT - 700, 0,0 };
		TextBox* GOScoreText = new TextBox(font, (char*)"Score: 0", black, GOScorePos, renderer);

		SDL_Rect GORetry = { SCREEN_WIDTH / 2 - 110, SCREEN_HEIGHT - 600, 0,0 };
		TextBox* GORetryText = new TextBox(font, (char*)"Play Again", white, GORetry, renderer);

		SDL_Rect GOMainMenu = { SCREEN_WIDTH / 2 - 120, SCREEN_HEIGHT - 500, 0,0 };
		TextBox* GOMenuText = new TextBox(font, (char*)"Go to Menu", white, GOMainMenu, renderer);


		//CREATE WAVES 

		Wave* wave1 = new Wave(1, 7, 3.5);
		Wave* wave2 = new Wave(2, 9, 2.5);
		Wave* wave3 = new Wave(3, 12, 2.1);
		Wave* wave4 = new Wave(4, 16, 1.6);


		//Wave* tempWave = new Wave(69, 1, 2);


		std::vector<Wave*> waves = { wave1, wave2, wave3, wave4 };
		//std::vector<Wave*> waves{ tempWave }; //TEMPORARY

		int wavePointer = 0;


		//DELAYS

		float enemyTimer = 0.0f;

		float enemySpawnRate = waves[0]->GetSpawnFrequency();


		float bossAttackTimer = 3.0f;

		float bossCooldown = 0;

		float bossInitDelay = 4.0f;

		float currentBossDelay = 0;

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

					closeGame = true;
					break;

				case SDL_MOUSEBUTTONDOWN:

					if (event.button.button == SDL_BUTTON_LEFT)
					{
						if (phase == GAME_OVER)
						{
							int x = event.button.x;
							int y = event.button.y;

							SDL_Point mousePos = { x, y };

							SDL_Rect retryPos = GORetryText->GetPositionRect();
							SDL_Rect backPos = GOMenuText->GetPositionRect();

							if (SDL_PointInRect(&mousePos, &retryPos))
							{
								//Reload level

								retry = true;
								quit = true;
							}

							if (SDL_PointInRect(&mousePos, &backPos))
							{
								//Go back to main menu

								retry = false;
								quit = true;
							}
						}

					}

				default:

					break;
				}
			}


			//DO FRAME LIMITING

			DoFrameLimiting(); //Calculates deltaTime



			if (phase == REGULAR_WAVE) 	//EXCLUSIVE STUFF FOR REGULAR WAVES
			{

				//CHECK IF NEW WAVE

				if (waves[wavePointer]->GetWaveEnd())
				{

					waveWarningText->ToggleVisibilty(true);

					if (wavePointer == waves.size() - 1)
					{
						if (currentBossDelay > bossInitDelay)
						{
							//Initiate boss wave after enemy waves

							phase = BOSS_WAVE;

							bosses.push_back(new Boss(renderer, (char*)"UFO.bmp", (SCREEN_WIDTH / 2) - 360, -180, 720, 280, 1.5, 90, &gameManager));

							bossAttackTimer = bosses[0]->GetAttackRate();

							waveWarningText->ToggleVisibilty(false); //HIDE WAVE WARNING

						}
						else
						{
							currentBossDelay += deltaTime;

							waveWarningText->ChangeText((char*)"BOSS WAVE!");

						}




					}
					else
					{
						wavePointer++;

						std::string waveTxt = "WAVE " + std::to_string(waves[wavePointer]->GetWaveNum());
						waveWarningText->ChangeText((char*)waveTxt.c_str());

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

					waveWarningText->ToggleVisibilty(false);

				}
				else
				{
					enemyTimer += deltaTime;
				}
			}




			if (phase == BOSS_WAVE) //BOSS WAVE EXCLUSIVE STUFF
			{
				bossCooldown += deltaTime;

				if (bossCooldown > bossAttackTimer)
				{
					int attackID = (rand() % 8) + 1;


					if (attackID == 1) //Spawn enemies 12.5% of the time
					{
						enemyCooldown = 0; //Reset cooldown so they don't fire before player can react

						bosses[0]->BackUpCall(enemies, 2);

					}
					else //Fire projectiles 85.5% of the time
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


						//GET VICTORY SCREEN

						phase = GAME_OVER;

						victory = true;
					}
				}


			}

			if (phase == BOSS_WAVE || phase == REGULAR_WAVE) //WAVE STUFF
			{
				//SPAWN ENEMY PROJECTILE

				if (enemies.size() != 0)
				{
					if (enemyCooldown > enemyFireRate)
					{
						int randEnemy = rand() % enemies.size();

						SDL_Rect position = enemies[randEnemy]->GetPosition();

						SDL_Point spawnPos{ position.x + (position.w / 2), position.y + (position.h / 2) };
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

				for (int i = 0; i < enemies.size(); i++) //Damage player if an enemy hits the bottom of the screen
				{
					if (enemies[i]->GetY() > SCREEN_HEIGHT)
					{
						player->health->TakeDamage(1);
					}
				}


				gameManager.UpdateEnemies(enemies, deltaTime); //Move and despawn enemies when offscreen

				gameManager.UpdateProjectiles(projectiles, deltaTime); //Move and despawn projectiles when offscreen


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





				//Check for Player LOSE

				if (!player->health->IsAlive())
				{
					phase = GAME_OVER;

					victory = false;
				}

			}




			//UPDATE TEXTBOXES


			std::string healthTxt = "Health: " + std::to_string(player->health->GetCurrentHealth());
			healthText->ChangeText(healthTxt.c_str());


			std::string scoreTxt = "Score: " + std::to_string(gameManager.GetScore());
			scoreText->ChangeText(scoreTxt.c_str());

			if (phase == REGULAR_WAVE)
			{
				std::string enemiesTxt = "Enemies Left: " + std::to_string(waves[wavePointer]->GetNumberOfEnemiesLeft());
				enemiesText->ChangeText(enemiesTxt.c_str());

			}
			else if (phase == BOSS_WAVE)
			{
				enemiesText->ChangeText("Enemies Left: ?");
			}
		
			//Clear Old Render

			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
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
			waveWarningText->DrawText();



			//Gameover menu
			
			if (phase == GAME_OVER)
			{
				SDL_Rect boxPos = { SCREEN_WIDTH / 2 - 190, SCREEN_HEIGHT - 720, 400, 320 };

				//DISPLAY GAME OVER MENU
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				SDL_RenderFillRect(renderer, &boxPos);//Draw Menu block


				SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
				boxPos = GORetryText->GetPositionRect();
				SDL_RenderFillRect(renderer, &boxPos);//Draw Retry button

				SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
				boxPos = GOMenuText->GetPositionRect();
				SDL_RenderFillRect(renderer, &boxPos); //Draw BackToMenu button


				GOScoreText->ChangeText(scoreTxt.c_str());

				GOScoreText->DrawText();
				GORetryText->DrawText();
				GOMenuText->DrawText();

			}
			//Present Render each Frame

			SDL_RenderPresent(renderer);


		}

		//Delete 

		for (int i = 0; i < waves.size(); i++)
		{
			delete waves[i];
		}


		delete player;

	}
	


}

