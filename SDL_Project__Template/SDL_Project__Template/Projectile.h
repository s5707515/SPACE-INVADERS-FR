#pragma once

#include "Sprite.h"

class Projectile : public Sprite
{


public:

	enum Direction //Used to specify the direction the projectile is travelling
	{
		UP,

		DOWN
	};

	enum Team //Used to work out what objects the projectile can damage
	{
		PLAYER_TEAM,

		ENEMY_TEAM
	};


	Team GetTeam() { return team; }

	Projectile(SDL_Renderer* _renderer, char* file, int _x, int _y, int _w, int _h, int _speed, Direction _dir, Team _team);

	void MoveProjectile(float _deltaTime);

private:

	int speed;

	Direction dir;

	Team team;

};