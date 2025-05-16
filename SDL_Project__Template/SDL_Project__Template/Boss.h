#pragma once

#include "Sprite.h"
#include "Health.h"

class Boss : public Sprite
{
private:

	int speed = 1;


public:

	Health* health;

	Boss(SDL_Renderer* _renderer, char* _file, int _x, int _y, int _w, int _h, int _speed, int _maxHealth); //CTOR

	~Boss(); //DTOR

	void MoveBoss(float _deltaTime);

};