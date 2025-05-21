#include "Enemy.h"


Enemy :: Enemy(SDL_Renderer* _renderer, char* _file, int _x, int _y, int _w, int _h, int _speed, int _maxHealth, Wave* &_wave) : Sprite(_renderer, _file, _x, _y, _w, _h)
{
	speed = _speed;

	health = new Health(_maxHealth);

	wave = _wave;

	wave->IncrementAliveEnemies();

	partOfWave = true;

} //CTOR

Enemy::Enemy(SDL_Renderer* _renderer, char* _file, int _x, int _y, int _w, int _h, int _speed, int _maxHealth) : Sprite(_renderer, _file, _x, _y, _w, _h)
{
	speed = _speed;

	health = new Health(_maxHealth);

	partOfWave = false;

	wave = nullptr;
} //CTOR

Enemy:: ~Enemy()
{

	if (health != nullptr)
	{
		delete health;
	}

	if (partOfWave)
	{
		if (wave != nullptr)
		{
			wave->DecrementNumberOfEnemies(); //Decrement wave count when an enemy is killed
		}
	}
}

	

void Enemy::MoveEnemy(float _deltaTime) //Move enemy down the screen
{
	truePos.y += speed * _deltaTime * 10;
}

