#include "Player.h"
#include <vector>


Player::Player(SDL_Renderer* _renderer, char* _file, int _x, int _y, int _w, int _h, GameManager* _gameManager) : Sprite(_renderer, _file, _x, _y, _w, _h) 
{
	gameManager = _gameManager;

} //CTOR

//DONT NEED DTOR AS INHERIT SPRITE 

void Player::Move(float _deltaTime)
{
	//GET KEYBOARD

	const Uint8* key = SDL_GetKeyboardState(NULL);

	if (truePos.x + position.w < rightBorderPos)
	{
		if (key[SDL_SCANCODE_RIGHT] || key[SDL_SCANCODE_D])
		{
			truePos.x += speed * _deltaTime * 10;
		}
	}
	
	if (truePos.x > leftBorderPos)
	{
		if (key[SDL_SCANCODE_LEFT] || key[SDL_SCANCODE_A])
		{
			truePos.x -= speed * _deltaTime * 10;
		}
	}

}

void Player::Shoot(std::vector<Projectile*>& _projectiles)
{
	const Uint8* key = SDL_GetKeyboardState(NULL);

	if (key[SDL_SCANCODE_SPACE])
	{
		SDL_Point spawnPos{ position.x + (position.w /2), position.y - (position.h / 2)}; //Spawn projectile above player
		gameManager->CreateProjectile(renderer, _projectiles, Projectile::Team::PLAYER_TEAM, spawnPos);
	}
}