
#include "Boss.h"

Boss::Boss(SDL_Renderer* _renderer, char* _file, int _x, int _y, int _w, int _h, int _speed, int _maxHealth, GameManager* _gameManager):Sprite( _renderer,  _file,  _x,  _y,  _w,  _h)
{
	speed = _speed;

	health = new Health(_maxHealth);

	gameManager = _gameManager;

	alternateShot = false;
}

Boss::~Boss()
{
	if (health != nullptr)
	{
		delete health;
	}
}

void Boss::MoveBoss(float _deltaTime)
{
	if (truePos.y < stopHeight)
	{
		truePos.y += speed * _deltaTime * 10;
	}
	
}


void Boss::FireBarrage(std::vector<Projectile*>& _projectiles, int _numProjectiles)
{
	SDL_Point spawnPos;

	float distanceBetweenShots = GetW() / (_numProjectiles - 1);

	if (alternateShot)
	{
		for (int i = 0; i < _numProjectiles - 1; i++)
		{
			spawnPos.x = GetX() + (i * distanceBetweenShots) + (0.5 * distanceBetweenShots);
			spawnPos.y = GetY() + GetH();

			gameManager->CreateProjectile(renderer, _projectiles, Projectile::Team::ENEMY_TEAM, spawnPos);
		}

		alternateShot = false;
	}
	else
	{
		for (int i = 0; i < _numProjectiles; i++)
		{

			spawnPos.x = GetX() + (i * distanceBetweenShots);
			spawnPos.y = GetY() + GetH();

			gameManager->CreateProjectile(renderer, _projectiles, Projectile::Team::ENEMY_TEAM, spawnPos);
		}

		alternateShot = true;
	}
	
}

void Boss::BackUpCall(std::vector<Enemy*>& _enemies, int _numEnemies)
{
	for (int i = 0; i < _numEnemies; i++)
	{
		gameManager->CreateEnemyForBoss(renderer, _enemies, position);
	}
}