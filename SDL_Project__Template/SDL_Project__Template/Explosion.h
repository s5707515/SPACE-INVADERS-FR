#pragma once

#include "Sprite.h"

//CLASS USED TO DISPLAY ANIMATED SPRITES (IN THIS CASE ONLY EXPLOSIONS)

class Explosion :public Sprite
{
private:

	int numFrames; //The number of frames in a spritesheet

	int currentFrame{ 0 };

	int frameWidth;

	int frameHeight;

	float duration; //How long one cycle of the animation plays


	float frameTime; //The time each frame is on screen

	float currentTime{ 0 };

	bool isDone = false; //checks if the animation has been completed

	float scale; //The size of the animation


public:

	Explosion(SDL_Renderer* _renderer, char* _imageFile, int _x, int _y, int _w, int _h, int _numFrames, float _duration, float _scale);

	~Explosion();

	void DrawAnimation(float _deltaTime); //Displays animation to window

	bool IsDone() { return isDone; }
};
