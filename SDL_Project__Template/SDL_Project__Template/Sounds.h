#pragma once

#include <SDL_mixer.h>

class Music
{
private:

	char* fileName;

	Mix_Music* music{ nullptr };

public:

	Music(const char* _fileName); //CTOR
	~Music(); //DTOR

	void PlayMusic();
};