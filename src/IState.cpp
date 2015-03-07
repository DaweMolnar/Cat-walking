#include "IState.h"

IState::IState(SDL_Window& window) : font_(nullptr), run_(true), win_(window) 
{
	ren_ = SDL_CreateRenderer(&win_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren_ == 0) {
		throw std::runtime_error(SDL_GetError());
	}

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
		throw std::runtime_error(SDL_GetError());
	}
	TTF_Init();
}

void
IState::renderText(const SDL_Color& color,SDL_Rect& destination, const std::string& text)
{
	if(font_ == nullptr) {
		throw std::runtime_error("No font declared");
	}
	SDL_Surface *surf = TTF_RenderText_Blended(font_, text.c_str(), color);
	SDL_Texture* score = SDL_CreateTextureFromSurface(ren_, surf);
	SDL_FreeSurface(surf);
	SDL_QueryTexture(score, NULL, NULL, &destination.w, &destination.h);
	SDL_RenderCopy(ren_, score, NULL, &destination);
}
