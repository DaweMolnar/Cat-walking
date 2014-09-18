#include "MenuState.h"
#include <iostream>

MenuState::MenuState(SDL_Window& window)
:
	IState(window),
	retCause_(0)
{
	background_ = IMG_LoadTexture(ren_, "Sprites/background.png");
	if (background_ == 0) {
		throw std::runtime_error(SDL_GetError());
	}
	font_ = TTF_OpenFont("sample.ttf", 40);
}

void
MenuState::renderItems()
{
	SDL_RenderClear(ren_);
	SDL_RenderCopy(ren_, background_, NULL, NULL);
	
	SDL_Color color = { 255, 255, 255, 255 };
	SDL_Rect destination;
	destination.x = 220;
	destination.y = 150;
	renderText(color,destination,"Game Over");
	
	SDL_RenderPresent(ren_);
}

void
MenuState::handleEvents(SDL_Event &e)
{
	switch (e.type) {
		case SDL_KEYDOWN:
			//if(e.key.keysym.sym == SDL_SCANCODE_RETURN) {
				//std::cout << "RETURN PRESSED" << std::endl;
				run_ = false;
			//}
			break;
		case SDL_QUIT:
			retCause_ = -1;
			run_ = false;
			break;
		default:
			run_ = true;
			break;
	}
}

int
MenuState::EventLoop()
{
	renderItems();
	while(run_) {
		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			handleEvents(e);
		}
	}
	return retCause_;
}

MenuState::~MenuState()
{
	SDL_DestroyRenderer(ren_);
}
