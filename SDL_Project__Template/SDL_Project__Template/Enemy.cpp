#include "Enemy.h"

Enemy :: Enemy(SDL_Renderer* _renderer, char* _file, int _x, int _y, int _w, int _h, int _speed) : Sprite(_renderer, _file, _x, _y, _w, _h) 
{
	speed = _speed;

} //CTOR

void Enemy::MoveEnemy(float _deltaTime) //Move enemy down the screen
{
	truePos.y += speed * _deltaTime * 10;
}

