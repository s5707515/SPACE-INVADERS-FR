
#include "Sounds.h"
#include <SDL.h>

#include <iostream>

Music::Music(const char* _fileName)
{
	fileName = _fileName;


	music = Mix_LoadMUS(fileName);

	if (!music)
	{
		std::cout << "Failed to load music: " << Mix_GetError() << std::endl;

	}
}



Music::~Music()
{
	if (music != nullptr)
	{
		Mix_FreeMusic(music);
		music = nullptr;
	}
}

void Music::PlayMusic()
{
	Mix_PlayMusic(music, -1); //Loop music infinitely
}

SFX::SFX(const char* _fileName, int _volume)
{
	fileName = _fileName;

	sound = Mix_LoadWAV(fileName);

	if (!sound)
	{
		std::cout << "Failed to load SFX: " << Mix_GetError() << std::endl;


		if (_volume > 128) //Clamp volume to supported size
		{
			volume = 128;
		}
		else if (_volume < 0)
		{
			volume = 0;
		}
		else
		{
			volume = volume;
		}

		Mix_VolumeChunk(sound, volume);
	}


}


SFX::~SFX()
{
	if (!sound)
	{
		Mix_FreeChunk(sound);
		sound = nullptr;
	}
}


void SFX::PlaySound()
{
	Mix_PlayChannel(-1, sound, 0);
}