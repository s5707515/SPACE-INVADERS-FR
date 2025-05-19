#pragma once

#include <SDL_mixer.h>

class Music
{
private:

	const char* fileName;

	Mix_Music* music{ nullptr };


public:

	Music(const char* _fileName); //CTOR
	~Music(); //DTOR

	void PlayMusic();
};


class SFX
{
private:


	const char* fileName;

	Mix_Chunk* sound{ nullptr };

	int volume{ 10 };

public:

	SFX(const char* _fileName, int _volume); //CTOR
	~SFX(); //DTOR

	void PlaySound(); //Plays sound effect



};