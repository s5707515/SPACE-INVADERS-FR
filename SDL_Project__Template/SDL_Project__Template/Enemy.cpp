#include "Enemy.h"

Enemy :: Enemy(SDL_Renderer* _renderer, char* _file, int _x, int _y, int _w, int _h, int _speed) : Sprite(_renderer, _file, _x, _y, _w, _h) 
{
	speed = _speed;

} //CTOR

void Enemy::MoveEnemy() //Move enemy down the screen
{
	position.y += speed;
}

