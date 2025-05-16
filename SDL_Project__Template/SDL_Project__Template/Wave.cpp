
#include "Wave.h"

#include <iostream>

Wave::Wave(int _waveNum, int _numberOfEnemies, float _spawnFrequency)
{
	
	waveNum = _waveNum;

	numberOfEnemiesLeft = _numberOfEnemies;

	numOfEnemiesAlive = 0;

	spawnFrequency = _spawnFrequency;

	if (numberOfEnemiesLeft >= 0)
	{
		waveEnd = false;
	}
	else
	{
		waveEnd = true; //stop a wave of 0 or less attempting to spawn
	}


}




void Wave::DecrementNumberOfEnemies()
{
	numberOfEnemiesLeft--;

	numOfEnemiesAlive--;

	if (numberOfEnemiesLeft <= 0)
	{
		waveEnd = true;
	}
}

