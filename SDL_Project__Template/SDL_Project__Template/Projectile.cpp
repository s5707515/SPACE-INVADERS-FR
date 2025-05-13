
#include "Projectile.h"


Projectile::Projectile(SDL_Renderer* _renderer, char* _file, int _x, int _y, int _w, int _h, int _speed, Direction _dir, Team _team) : Sprite(_renderer, _file, _x, _y, _w, _h)
{
	speed = _speed;

	dir = _dir;

	team = _team;
}


void Projectile::MoveProjectile(float _deltaTime)
{
	switch (dir) //Move projectile based on the direction it is facing
	{
		case UP:

			truePos.y -= speed * _deltaTime * 10;

			break;

		case DOWN:

			truePos.y += speed * _deltaTime * 10;
	}
}