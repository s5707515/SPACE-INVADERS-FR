
#include "Projectile.h"


Projectile::Projectile(SDL_Renderer* _renderer, char* _file, int _x, int _y, int _w, int _h, int _speed, Team _team, int _damage) : Sprite(_renderer, _file, _x, _y, _w, _h)
{
	speed = _speed;

	damage = _damage;

	team = _team;
}


void Projectile::MoveProjectile(float _deltaTime)
{
	switch (team) //Move projectile based on the direction it is facing
	{
		case PLAYER_TEAM:

			truePos.y -= speed * _deltaTime * 10;

			break;

		case ENEMY_TEAM:

			truePos.y += speed * _deltaTime * 10;
	}
}