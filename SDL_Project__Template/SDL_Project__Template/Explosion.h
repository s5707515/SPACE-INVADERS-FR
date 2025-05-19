#pragma once

#include "Sprite.h"

class Explosion :public Sprite
{
private:

	int numFrames;

	int currentFrame{ 0 };

	int frameWidth;

	int frameHeight;
	float duration;


	float frameTime;

	float currentTime{ 0 };

	bool isDone = false;

	float scale;


public:

	Explosion(SDL_Renderer* _renderer, char* _imageFile, int _x, int _y, int _w, int _h, int _numFrames, float _duration, float _scale);

	~Explosion();

	void DrawAnimation(float _deltaTime);

	bool IsDone() { return isDone; }
};
