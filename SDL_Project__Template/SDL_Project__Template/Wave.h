#pragma once


#include <SDL.h>

class Wave 
{
private:

	float spawnFrequency;

	int numberOfEnemiesLeft;

	int numOfEnemiesAlive;
	
	int waveNum{ 0 };

	bool waveEnd = false;



public:

	Wave(int waveNum, int _numberOfEnemies, float _spawnFrequency);

	//GETTERS

	int GetWaveNum() { return waveNum;}

	int GetNumberOfEnemiesLeft() { return numberOfEnemiesLeft; }

	bool GetWaveEnd() { return waveEnd; }

	float GetSpawnFrequency() { return spawnFrequency; }

	void DecrementNumberOfEnemies();

	void IncrementAliveEnemies() { numOfEnemiesAlive++;  }

	int GetNumberOfEnemiesAlive() { return numOfEnemiesAlive; }
	
};