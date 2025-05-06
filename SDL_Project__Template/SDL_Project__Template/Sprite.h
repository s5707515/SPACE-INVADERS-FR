#pragma once


#include <SDL.h>

class Sprite
{

protected:

	SDL_Texture* image;

	SDL_Rect position; //The images proportions

	SDL_Renderer* renderer; //The renderer the sprites are drawn to

public:

	Sprite(SDL_Renderer* _renderer, char* imageFile, int _x, int _y, int _w, int _h); //CTOR

	virtual ~Sprite(); //DTOR

	//SETTERS

	void SetX(int _x) { position.x = _x; }
	void SetY(int _y) { position.y = _y; }

	//GETTERS

	int GetX() { return position.x; }
	int GetY() { return position.y; }

	SDL_Rect& GetPosition() { return position; }


	void DrawSprite();

};