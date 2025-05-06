#include "Player.h"

Player::Player(SDL_Renderer* _renderer, char* _file, int _x, int _y, int _w, int _h) : Sprite(_renderer, _file, _x, _y, _w, _h) {} //CTOR

//DONT NEED DTOR AS INHERIT SPRITE 