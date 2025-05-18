
#include "UI.h"

#include <iostream>

TextBox::TextBox(TTF_Font* _font, char* _text, SDL_Color _colour, SDL_Rect pos, SDL_Renderer* _renderer)
{

	//Set variables
	font = _font;

	colour = _colour;

	position = pos;


	renderer = _renderer;

	visibility = true;

	ChangeText(_text);
	
}

void TextBox::ChangeText(const char* _newText)
{
	text = (char*)_newText;

	SDL_Surface* txtSurface{ nullptr };

	txtSurface = TTF_RenderText_Blended_Wrapped(font, text, colour,900);

	if (!txtSurface)
	{
		std::cout << "Failed to render text: " << TTF_GetError() << std::endl;

		system("pause");
	}
	else
	{
		if (textTexture != nullptr)
		{
			//Destroy old texture

			SDL_DestroyTexture(textTexture);
			textTexture = nullptr;
		}
		position.w = txtSurface->w;
		position.h = txtSurface->h;

		textTexture = SDL_CreateTextureFromSurface(renderer, txtSurface);
		SDL_FreeSurface(txtSurface);

		if (textTexture == 0)
		{
			std::cout << "Failed to create texture from surface: " << SDL_GetError() << std::endl;

			system("pause");
		}

	}

	
}


void TextBox::DrawText()
{
	if (visibility)
	{
		SDL_RenderCopy(renderer, textTexture, NULL, &position);
	}
	
}

void TextBox::ToggleVisibilty(bool _visibility)
{
	visibility = _visibility;
}