#pragma once

//PLAYER SPACESHIP CLASS

#include "Sprite.h"

#include "Health.h"
#include "Projectile.h"
#include "GameManager.h"

class Player : public Sprite
{

private:

	int speed = 50;

	int leftBorderPos = 0;

	int rightBorderPos = 800;

	float fireRate = 0.5f;

	float shotCoolDown = fireRate; //Allow player to shoot straight away

	GameManager* gameManager;

	

public:

	Health* health;


	Player(SDL_Renderer* _renderer, char* _file, int _x, int _y, int _w, int _h, GameManager* _gameManager, int _maxHealth); //CTOR

	~Player();//Dtor


	void Move(float _deltaTime); //Move the player left/right based on inputs

	void Shoot(std::vector<Projectile*>& _projectiles, float _deltaTime); //Spawn a projectile at players position

};
