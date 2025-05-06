#pragma once

//PLAYER SPACESHIP CLASS

#include "Sprite.h"

class Player : public Sprite
{
public:

	Player(SDL_Renderer* _renderer, char* _file, int _x, int _y, int _w, int _h);

	void Move();

};
