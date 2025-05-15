#pragma once

#include <SDL_ttf.h>

struct GameUI
{


};


class TextBox
{
private:

	TTF_Font* font{ nullptr };

	SDL_Color colour;

	SDL_Rect position;

	SDL_Renderer* renderer{ nullptr };

	SDL_Texture* textTexture;

	char* text;

public:

	TextBox(TTF_Font* _font, char* _text, SDL_Color _colour, SDL_Rect pos, SDL_Renderer* _renderer); //CTOR

	void ChangeText(char* _newText);

	void DrawText();
};
