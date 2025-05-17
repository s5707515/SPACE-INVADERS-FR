
#include "GameManager.h"
#include <iostream>

//Basically tidies up the GameLoop function.


void GameManager::CreateProjectile(SDL_Renderer* renderer, std::vector<Projectile*>& _projectiles, Projectile::Team team, SDL_Point _spawnPos)
{
	//SPAWN PROJECTILES WITH DIFFERENT ATTRIBUTES BASED ON TEAM

	switch (team)
	{
		case Projectile::Team::PLAYER_TEAM :

			_projectiles.push_back(new Projectile(renderer, (char*)"Projectile1.bmp", _spawnPos.x, _spawnPos.y, 8, 32, 75, Projectile::Team::PLAYER_TEAM,1));

			break;

		case Projectile::Team::ENEMY_TEAM:

			_projectiles.push_back(new Projectile(renderer, (char*)"Projectile2.bmp", _spawnPos.x, _spawnPos.y, 24, 24, 75, Projectile::Team::ENEMY_TEAM, 1));

			break;



		default:

			std::cout << "Couldn't find an applicable team for the projectile!" << std::endl;

	}
}

void GameManager::UpdateProjectiles(std::vector<Projectile*>& _projectiles, float _deltaTime) //Move projectiles and destroy once offscreen
{
	for (unsigned int i = 0; i < _projectiles.size(); i++)
	{
		_projectiles[i]->MoveProjectile(_deltaTime);

		if (_projectiles[i]->GetY() < 0 || _projectiles[i]->GetY() > SCREEN_HEIGHT)
		{
			std::cout << "Deleted Projectile!" << std::endl;

			delete _projectiles[i];
			_projectiles.erase(_projectiles.begin() + i);
			i--;
		}

	}
}

void GameManager::CreateEnemyForBoss(SDL_Renderer* renderer, std::vector<Enemy*>& _enemies, SDL_Rect bossPos) //Used for BOSS
{
	int enemyID = rand() % 3;

	Enemy* newEnemy = nullptr;

	bool freeSpace = true;

	int xPos = 0;

	do
	{
		freeSpace = true; //Assume there is a free space to spawn enemy

		xPos = (rand() % bossPos.w - 48) + bossPos.x; //Generate xPos for spawnPoint

		SDL_Rect spawnCheck = { xPos, 0,96, SCREEN_HEIGHT };

		for (int i = 0; i < _enemies.size(); i++) //Check that no enemies exist in this column (STOP ENEMIES OVERLAPPING)
		{
			if (_enemies[i]->CheckCollision(spawnCheck))
			{
				freeSpace = false;
			}
		}



	} while (!freeSpace);





	switch (enemyID)
	{
	case 0:
		//SPAWN SQUID

		_enemies.push_back(new Enemy(renderer, (char*)"Squid.bmp", xPos, bossPos.y + bossPos.h, 64, 64, 32, 1));

		break;

	case 1:
		//SPAWN CRAB

		_enemies.push_back(new Enemy(renderer, (char*)"Crab.bmp", xPos, bossPos.y + bossPos.h, 88, 64, 20, 2));

		break;

	case 2:
		//SPAWN OCTOPUS

		_enemies.push_back(new Enemy(renderer, (char*)"Octopus.bmp", xPos, bossPos.y + bossPos.h, 96, 64, 12, 3));

		break;
	}

}

void GameManager::CreateEnemy(SDL_Renderer* renderer, std::vector<Enemy*>& _enemies, Wave* &_wave) //Spawn a random enemy
{
	int enemyID = rand() % 3;

	Enemy* newEnemy = nullptr;

	bool freeSpace = true;

	int xPos = 0;

	do
	{
		freeSpace = true; //Assume there is a free space to spawn enemy

		xPos = rand() % (SCREEN_WIDTH - 96); //Generate xPos for spawnPoint

		SDL_Rect spawnCheck = { xPos, 0,96, SCREEN_HEIGHT }; 

		for (int i = 0; i < _enemies.size(); i++) //Check that no enemies exist in this column (STOP ENEMIES OVERLAPPING)
		{
			if (_enemies[i]->CheckCollision(spawnCheck))
			{
				freeSpace = false;
			}
		}



	} while (!freeSpace);

	
	switch (enemyID)
	{
	case 0:
		//SPAWN SQUID

		_enemies.push_back(new Enemy(renderer, (char*)"Squid.bmp", xPos, 0, 64, 64, 32,1, _wave));

		break;

	case 1:
		//SPAWN CRAB

		_enemies.push_back(new Enemy(renderer, (char*)"Crab.bmp", xPos, 0, 88, 64, 20,2, _wave));

		break;

	case 2:
		//SPAWN OCTOPUS

		_enemies.push_back(new Enemy(renderer, (char*)"Octopus.bmp", xPos, 0, 96, 64, 12,3,_wave));

		break;
	}

}

void GameManager::UpdateEnemies(std::vector<Enemy*>& _enemies, float _deltaTime) //Move enemies and destroy once offscreen
{
	for (unsigned int i = 0; i < _enemies.size(); i++)
	{
		_enemies[i]->MoveEnemy(_deltaTime);

		//CHECK TO DESTROY ENEMIES

		if (_enemies[i]->GetY() > SCREEN_HEIGHT)
		{
			std::cout << "Deleted enemy: " << _enemies[i] << std::endl;

			delete _enemies[i];
			_enemies.erase(_enemies.begin() + i);
			i--;
		}

	}
}

void GameManager::IncrementScore(int _points)
{
	score += _points;
}


