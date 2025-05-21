#pragma once

#include <SDL_ttf.h>

//CLass for displaying text to the screen

class TextBox
{
private:

	TTF_Font* font{ nullptr }; //The font type

	SDL_Color colour;

	SDL_Rect position;

	SDL_Renderer* renderer{ nullptr };

	SDL_Texture* textTexture; 

	char* text; //The text that will be displayed

	bool visibility; //Determines if the textbox is on screen

public:

	TextBox(TTF_Font* _font,char* _text, SDL_Color _colour, SDL_Rect pos, SDL_Renderer* _renderer); //CTOR

	~TextBox() {}; //DTOR

	void ChangeText(const char* _newText); //Alter the text in the textbox

	void DrawText(); //Make the text visible to the window

	void ToggleVisibilty(bool _visibility); //Change whether text can or cant be seen

	SDL_Rect GetPositionRect() { return position; }
};
