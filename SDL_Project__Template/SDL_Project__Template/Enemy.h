#pragma once

//CLASS FOR ALL ENEMIES

#include "Sprite.h"

#include "Health.h"

#include "Wave.h"


class Enemy : public Sprite
{

private:

	int speed = 1;

	Wave* wave{ nullptr };

	bool partOfWave;


public:

	Health* health;

	bool GetPartOfWave() { return partOfWave; }

	Enemy(SDL_Renderer* _renderer, char* file, int _x, int _y, int _w, int _h, int _speed, int _maxHealth, Wave* &_wave);//CTOR
	Enemy(SDL_Renderer* _renderer, char* file, int _x, int _y, int _w, int _h, int _speed, int _maxHealth);//CTOR (For enemies that are spawned by boss_

	~Enemy(); //DTOR

	void MoveEnemy(float _deltaTime); //Moves enemy down the screen
};