#pragma once

#include "Sprite.h"
#include "Health.h"
#include "Projectile.h"
#include "GameManager.h"

#include <Vector>



class Boss : public Sprite
{
private:

	int speed = 1;

	int stopHeight = 250; //Height boss stops moving forward at

	float attackRate = 3.0f;

	GameManager* gameManager;

	bool alternateShot = false;


public:

	Health* health;

	float GetAttackRate() { return attackRate; }

	Boss(SDL_Renderer* _renderer, char* _file, int _x, int _y, int _w, int _h, int _speed, int _maxHealth, GameManager* _gameManager); //CTOR

	~Boss(); //DTOR

	void MoveBoss(float _deltaTime);

	void FireBarrage(std::vector<Projectile*>& _projectiles, int _numProjectiles);

	void BackUpCall(std::vector<Enemy*>& _enemies, int _numEnemies);

};