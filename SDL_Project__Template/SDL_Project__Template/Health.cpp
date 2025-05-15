
#include "Health.h"

Health::Health(int _maxHealth)
{
	maxHealth = _maxHealth;

	currentHealth = maxHealth; //Make it so object starts at full hp

	isAlive = true;
}

void Health::TakeDamage(int _damage)
{
	if (currentHealth < _damage)
	{
		currentHealth = 0;
	}
	else
	{
		currentHealth -= _damage;
	}

	if (currentHealth == 0) //Set object as dead
	{
		isAlive = false;
	}
}

