#pragma once

//CLASS FOR ALL ENEMIES

#include "Sprite.h"


class Enemy : public Sprite
{

private:

	int speed = 1;

public:

	Enemy(SDL_Renderer* _renderer, char* file, int _x, int _y, int _w, int _h, int _speed);//CTOR

	void MoveEnemy();
};