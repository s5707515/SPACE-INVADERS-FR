#pragma once

#include <SDL.h>
#include "Enemy.h"

#include <vector>


class GameManager
{
private:

	int SCREEN_WIDTH;

	int SCREEN_HEIGHT;

public:

	GameManager(int _screenW, int _screenH) { SCREEN_WIDTH = _screenW; SCREEN_HEIGHT = _screenH; }//CTOR

	void CreateEnemy(SDL_Renderer* renderer, std::vector<Enemy*>& _enemies);

	void UpdateEnemies(std::vector<Enemy*>& _enemies, float _deltaTime);

	

};

