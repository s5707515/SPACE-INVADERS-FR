
#include "GameManager.h"
#include <iostream>





void GameManager::CreateEnemy(SDL_Renderer* renderer, std::vector<Enemy*>& _enemies)
{
	int enemyID = rand() % 3;

	Enemy* newEnemy = nullptr;

	int xPos = rand() % SCREEN_WIDTH + 1;

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

