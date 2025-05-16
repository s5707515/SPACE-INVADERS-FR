#pragma once

#include "Sprite.h"

class Projectile : public Sprite
{


public:


	enum Team //Used to work out what objects the projectile can damage and what direction the object is shot
	{
		PLAYER_TEAM,

		ENEMY_TEAM
	};


	Team GetTeam() { return team; } //Return the "team" the projectile is on (Controls what GameObjects it can hurt)

	int GetDamage() { return damage; } //Returns damage

	Projectile(SDL_Renderer* _renderer, char* file, int _x, int _y, int _w, int _h, int _speed, Team _team, int _damage); //CTOR

	~Projectile() {}; //DTOR

	void MoveProjectile(float _deltaTime); //Moves the projectile up/down the screen 

private:

	int speed;

	int damage;

	Team team;

};