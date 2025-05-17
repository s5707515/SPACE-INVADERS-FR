#pragma once

#include <SDL.h>
#include "Enemy.h"
#include "Projectile.h"


#include <vector>


class GameManager
{
private:

	int SCREEN_WIDTH;

	int SCREEN_HEIGHT;

	int score = 0;


public:

	GameManager(int _screenW, int _screenH) { SCREEN_WIDTH = _screenW; SCREEN_HEIGHT = _screenH; }//CTOR

	~GameManager() {}; //DTOR

	void CreateEnemy(SDL_Renderer* renderer, std::vector<Enemy*>& _enemies, Wave* &_wave); //Instantiates a new enemy (Squid / Crab / Octopus)

	void CreateEnemyForBoss(SDL_Renderer* renderer, std::vector<Enemy*>& _enemies, SDL_Rect bossPos);

	void UpdateEnemies(std::vector<Enemy*>& _enemies, float _deltaTime); //Moves enemies down the screen, destroying them if they hit the bottom

	void CreateProjectile(SDL_Renderer* renderer, std::vector<Projectile*>& _projectiles, Projectile::Team team, SDL_Point _spawnPos); //Instantiates a new projectile

	void UpdateProjectiles(std::vector<Projectile*>& _projectiles, float _deltaTime); //Moves projectile up/down screen, destroying them if they go off screen
	
	int GetScore(){ return score; }

	void IncrementScore(int _points);

};

