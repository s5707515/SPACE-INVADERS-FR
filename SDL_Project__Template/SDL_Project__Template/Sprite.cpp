#include "Sprite.h"

#include <iostream>

Sprite::Sprite(SDL_Renderer* _renderer, char* _imageFile, int _x, int _y, int _w, int _h)
{
	renderer = _renderer;

	//INITIALISE POSITION VALUES
	position.x = _x;
	position.y = _y;
	position.w = _w;
	position.h = _h;


	truePos.x = _x;
	truePos.y = _y;

	SDL_Surface* file = SDL_LoadBMP(_imageFile);

	if (file == nullptr)
	{
		std::cout << "Failed to load bmp file: " << SDL_GetError() << std::endl;

	}

	image = SDL_CreateTextureFromSurface(_renderer, file);
	SDL_FreeSurface(file);

	if (image == nullptr)
	{
		std::cout << "Failed to create texture from surface: " << SDL_GetError() << std::endl;
	}




}

Sprite::~Sprite()
{
	if (image) //If an image was sucessfully created
	{
		SDL_DestroyTexture(image);
	}
}

void Sprite::DrawSprite() //Draw sprite on the screen 
{
	position.x = static_cast<int>(truePos.x);
	position.y = static_cast<int>(truePos.y);

	SDL_RenderCopy(renderer, image, NULL, &position);
}

bool Sprite::CheckCollision(SDL_Rect _other) //Check to see if another object has collided with this object
{
	return SDL_HasIntersection(&position, &_other);
}
