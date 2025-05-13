#pragma once

//PLAYER SPACESHIP CLASS

#include "Sprite.h"

#include "Projectile.h"
#include "GameManager.h"

class Player : public Sprite
{

private:

	int speed = 50;

	int leftBorderPos = 0;

	int rightBorderPos = 800;

	GameManager* gameManager;

public:


	Player(SDL_Renderer* _renderer, char* _file, int _x, int _y, int _w, int _h, GameManager* _gameManager);

	void Move(float _deltaTime);

	void Shoot(std::vector<Projectile*>& _projectiles);

};
