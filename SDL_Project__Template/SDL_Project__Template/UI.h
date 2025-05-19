#pragma once

#include <SDL_ttf.h>



class TextBox
{
private:

	TTF_Font* font{ nullptr };

	SDL_Color colour;

	SDL_Rect position;

	SDL_Renderer* renderer{ nullptr };

	SDL_Texture* textTexture;

	char* text;

	bool visibility;

public:

	TextBox(TTF_Font* _font,char* _text, SDL_Color _colour, SDL_Rect pos, SDL_Renderer* _renderer); //CTOR

	~TextBox() {}; //DTOR

	void ChangeText(const char* _newText);

	void DrawText();

	void ToggleVisibilty(bool _visibility);

	SDL_Rect GetPositionRect() { return position; }
};
