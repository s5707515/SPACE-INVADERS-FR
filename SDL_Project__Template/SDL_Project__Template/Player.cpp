#include "Player.h"

Player::Player(SDL_Renderer* _renderer, char* _file, int _x, int _y, int _w, int _h) : Sprite(_renderer, _file, _x, _y, _w, _h) {} //CTOR

//DONT NEED DTOR AS INHERIT SPRITE 

void Player::Move()
{
	//GET KEYBOARD

	const Uint8* key = SDL_GetKeyboardState(NULL);

	if (position.x + position.w < rightBorderPos)
	{
		if (key[SDL_SCANCODE_RIGHT] || key[SDL_SCANCODE_D])
		{
			position.x += speed;
		}
	}
	
	if (position.x > leftBorderPos)
	{
		if (key[SDL_SCANCODE_LEFT] || key[SDL_SCANCODE_A])
		{
			position.x -= speed;
		}
	}

}