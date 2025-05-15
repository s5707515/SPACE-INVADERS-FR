#pragma once


struct Health
{
private:

	int currentHealth;

	int maxHealth;

	bool isAlive;



public:

	Health(int _maxHealth); //CTOR

	int GetCurrentHealth() { return currentHealth; }
	
	bool IsAlive() { return isAlive; }

	void TakeDamage(int _damage);
};