
#include "Boss.h"

Boss::Boss(SDL_Renderer* _renderer, char* _file, int _x, int _y, int _w, int _h, int _speed, int _maxHealth):Sprite( _renderer,  _file,  _x,  _y,  _w,  _h)
{
	speed = _speed;

	health = new Health(_maxHealth);
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
	truePos.y += speed * _deltaTime * 10;
}