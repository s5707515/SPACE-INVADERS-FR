
#include "Explosion.h"

Explosion::Explosion(SDL_Renderer* _renderer, char* _imageFile, int _x, int _y, int _w, int _h, int _numFrames, float _duration, float _scale) : Sprite(_renderer, _imageFile, _x, _y, _w, _h)
{
	numFrames = _numFrames; //The number of frames to swap the sprite through

	duration = _duration; //The duration of the animation

	frameWidth = position.w / numFrames;

	frameHeight = position.h;

	frameTime = duration / numFrames;

	scale = _scale;
}

Explosion::~Explosion(){};

void Explosion::DrawAnimation(float _deltaTime) 
{
	if (!isDone)
	{
		currentTime += _deltaTime;

		if (currentTime > frameTime) //Change frame after a certain amount of time
		{
			currentFrame++;

			currentTime = 0;
		}
	}

	if (currentFrame == numFrames)
	{
		isDone = true; //Animation is complete
	}


	if (!isDone)
	{
		//Render specific frame

		SDL_Rect frameRect = { currentFrame * frameWidth, 0, frameWidth, frameHeight };

		SDL_Rect displayRect = { position.x, position.y, frameWidth * scale, frameHeight * scale};

		SDL_RenderCopy(renderer, image, &frameRect, &displayRect); 
	}

	
	
};