
#include "GameManager.h"
#include <iostream>



void GameManager::CreateProjectile(SDL_Renderer* renderer, std::vector<Projectile*>& _projectiles, Projectile::Team team, SDL_Point _spawnPos)
{
	switch (team)
	{
	case Projectile::Team::PLAYER_TEAM :

		_projectiles.push_back(new Projectile(renderer, (char*)"Projectile1.bmp", _spawnPos.x, _spawnPos.y, 8, 32, 75, Projectile::Direction::UP, Projectile::Team::PLAYER_TEAM));

		break;

	default:

		std::cout << "Couldn't find an applicable team for the projectile!" << std::endl;

	}
}

void GameManager::UpdateProjectiles(std::vector<Projectile*>& _projectiles, float _deltaTime)
{
	for (unsigned int i = 0; i < _projectiles.size(); i++)
	{
		_projectiles[i]->MoveProjectile(_deltaTime);

		if (_projectiles[i]->GetY() < 0 || _projectiles[i]->GetY() > SCREEN_HEIGHT)
		{
			std::cout << "Deleted Projectile!" << std::endl;

			_projectiles.erase(_projectiles.begin() + i);
		}

	}
}

void GameManager::CreateEnemy(SDL_Renderer* renderer, std::vector<Enemy*>& _enemies)
{
	int enemyID = rand() % 3;

	Enemy* newEnemy = nullptr;

	bool freeSpace = true;

	int xPos = 0;

	do
	{
		freeSpace = true; //Assume there is a free space to spawn enemy

		xPos = rand() % (SCREEN_WIDTH - 98) + 48; //Generate xPos for spawnPoint

		SDL_Rect spawnCheck = { xPos, 0,96, 40 }; //create a imaginary spawnPoint

		for (int i = 0; i < _enemies.size(); i++) //Check that no enemies exist at that spawnPoint
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

		_enemies.push_back(new Enemy(renderer, (char*)"Squid.bmp", xPos, 0, 64, 64, 40));

		break;

	case 1:
		//SPAWN CRAB

		_enemies.push_back(new Enemy(renderer, (char*)"Crab.bmp", xPos, 0, 88, 64, 30));

		break;


	case 2:
		//SPAWN OCTOPUS

		_enemies.push_back(new Enemy(renderer, (char*)"Octopus.bmp", xPos, 0, 96, 64, 20));

		break;
	}

}

void GameManager::UpdateEnemies(std::vector<Enemy*>& _enemies, float _deltaTime)
{
	for (unsigned int i = 0; i < _enemies.size(); i++)
	{
		_enemies[i]->MoveEnemy(_deltaTime);

		//CHECK TO DESTROY ENEMIES

		if (_enemies[i]->GetY() > SCREEN_HEIGHT)
		{
			std::cout << "Deleted enemy: " << _enemies[i] << std::endl;

			_enemies.erase(_enemies.begin() + i);
		}

	}

	/*std::vector<Enemy*>::iterator itr;
	for (itr = _enemies.begin(); itr != _enemies.end(); )
	{
		(*itr)->MoveEnemy();

		if ((*itr)->GetY() > SCREEN_HEIGHT)
		{
			std::cout << "Deleted enemy: " << *itr << std::endl;

			itr = _enemies.erase(itr);
		}
		else
		{
			itr++;
		}

	}
	*/
}



