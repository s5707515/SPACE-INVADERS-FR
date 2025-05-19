#include "Player.h"
#include <vector>


Player::Player(SDL_Renderer* _renderer, char* _file, int _x, int _y, int _w, int _h, GameManager* _gameManager, int _maxHealth) : Sprite(_renderer, _file, _x, _y, _w, _h) 
{
	gameManager = _gameManager;

	health = new Health(_maxHealth);

	lazer1 = new SFX("sfx_wpn_laser8.wav", 30);
	lazer2 = new SFX("sfx_wpn_laser6.wav", 30);
	lazer3 = new SFX("sfx_wpn_laser10.wav", 30);

} //CTOR

Player::~Player() //DTOR
{
	if (health != nullptr)
	{
		delete health;
	}

	delete lazer1;
	delete lazer2;
	delete lazer3;
}

void Player::Move(float _deltaTime)
{
	//GET KEYBOARD

	const Uint8* key = SDL_GetKeyboardState(NULL);

	if (truePos.x + position.w < rightBorderPos) //Check player is not at right edge of screen
	{
		if (key[SDL_SCANCODE_RIGHT] || key[SDL_SCANCODE_D]) //Move right when D or -> is pressed
		{
			truePos.x += speed * _deltaTime * 10;
		}
	}
	
	if (truePos.x > leftBorderPos) //Check player is not at leftedge of screen
	{
		if (key[SDL_SCANCODE_LEFT] || key[SDL_SCANCODE_A]) //Move left when a or <- is pressed
		{
			truePos.x -= speed * _deltaTime * 10;
		}
	}

}

void Player::Shoot(std::vector<Projectile*>& _projectiles, float _deltaTime) //Fire projectile
{
	const Uint8* key = SDL_GetKeyboardState(NULL);

	shotCoolDown += _deltaTime; //Increment cooldown

	if (key[SDL_SCANCODE_SPACE])
	{

		if (shotCoolDown > fireRate)
		{
			SDL_Point spawnPos{ position.x + (position.w / 2), position.y - (position.h / 2) }; //Set spawnpoint of projectile to above player
			gameManager->CreateProjectile(renderer, _projectiles, Projectile::Team::PLAYER_TEAM, spawnPos); //Get GameManager to spawn projectile

			int soundIndex = rand() % 3;

			switch (soundIndex)
			{
				case 0:

					lazer1->PlaySound();

					break;

				case 1:

					lazer2->PlaySound();

					break;

				case 2:

					lazer3->PlaySound();

					break;
			}
			shotCoolDown = 0;
		}
		
	}

	
}

