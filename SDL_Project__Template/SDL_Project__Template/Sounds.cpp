
#include "Sounds.h"

Music::Music(const char* _fileName)
{
	fileName = (char*)_fileName;

	music = Mix_LoadMUS(fileName);
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