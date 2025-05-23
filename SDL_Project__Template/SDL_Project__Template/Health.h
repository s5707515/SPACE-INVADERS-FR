#pragma once

// Basic health component class. Allows damage to be stored.

class Health
{
private:

	int currentHealth;

	int maxHealth;

	bool isAlive;



public:

	Health(int _maxHealth); //CTOR
	~Health() {}; //DTOR

	int GetCurrentHealth() { return currentHealth; }
	
	bool IsAlive() { return isAlive; }

	void TakeDamage(int _damage);
};