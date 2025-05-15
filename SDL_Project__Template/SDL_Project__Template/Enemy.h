#pragma once

//CLASS FOR ALL ENEMIES

#include "Sprite.h"

#include "Health.h"


class Enemy : public Sprite
{

private:

	int speed = 1;

	


public:

	Health* health;

	Enemy(SDL_Renderer* _renderer, char* file, int _x, int _y, int _w, int _h, int _speed, int _maxHealth);//CTOR

	~Enemy(); //DTOR

	void MoveEnemy(float _deltaTime); //Moves enemy down the screen
};