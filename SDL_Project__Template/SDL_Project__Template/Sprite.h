#pragma once


#include <SDL.h>

//class for displaying sprites to the window (needs to be inherited by all visible objects)

class Sprite
{

protected:

	SDL_Texture* image;

	SDL_Rect position; //The images proportions

	SDL_Renderer* renderer; //The renderer the sprites are drawn to

	SDL_FPoint truePos; //The position used for deltaTime (used since you can't render to float values)

public:

	Sprite(SDL_Renderer* _renderer, char* imageFile, int _x, int _y, int _w, int _h); //CTOR

	virtual ~Sprite(); //DTOR

	//SETTERS

	void SetX(int _x) { position.x = _x; }
	void SetY(int _y) { position.y = _y; }

	//GETTERS

	int GetX() { return position.x; }
	int GetY() { return position.y; }
	int GetW() { return position.w; }
	int GetH() { return position.h; }

	SDL_Rect& GetPosition() { return position; }


	void DrawSprite(); //Draws the sprite to the screen

	bool CheckCollision(SDL_Rect _other); //Returns true or false based on collision

};