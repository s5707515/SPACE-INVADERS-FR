#include "Player.h"

Player::Player(SDL_Renderer* _renderer, char* _file, int _x, int _y, int _w, int _h) : Sprite(_renderer, _file, _x, _y, _w, _h) {} //CTOR

//DONT NEED DTOR AS INHERIT SPRITE 

void Player::Move(float _deltaTime)
{
	//GET KEYBOARD

	const Uint8* key = SDL_GetKeyboardState(NULL);

	if (truePos.x + position.w < rightBorderPos)
	{
		if (key[SDL_SCANCODE_RIGHT] || key[SDL_SCANCODE_D])
		{
			truePos.x += speed * _deltaTime * 10;
		}
	}
	
	if (truePos.x > leftBorderPos)
	{
		if (key[SDL_SCANCODE_LEFT] || key[SDL_SCANCODE_A])
		{
			truePos.x -= speed * _deltaTime * 10;
		}
	}

}