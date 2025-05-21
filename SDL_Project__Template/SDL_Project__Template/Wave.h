#pragma once


#include <SDL.h>

//Class which stores wave properties and tracks wave progression

class Wave 
{
private:

	float spawnFrequency; //How often an enemy is spawn in the wave

	int numberOfEnemiesLeft; //How many enemies need to die before the wave is complete

	int numOfEnemiesAlive; //The number of enemies currently alive on the window
	
	int waveNum{ 0 }; //The wave ID

	bool waveEnd = false; //Has the wave been completed?



public:

	Wave(int waveNum, int _numberOfEnemies, float _spawnFrequency); //CTOR

	~Wave() {}; //DTOR

	//GETTERS

	int GetWaveNum() { return waveNum;}

	int GetNumberOfEnemiesLeft() { return numberOfEnemiesLeft; }

	bool GetWaveEnd() { return waveEnd; }

	float GetSpawnFrequency() { return spawnFrequency; }

	

	int GetNumberOfEnemiesAlive() { return numOfEnemiesAlive; }

	//METHODS

	void DecrementNumberOfEnemies(); 
	
	void IncrementAliveEnemies() { numOfEnemiesAlive++; }
};