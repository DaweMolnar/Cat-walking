#include "SDL_Main.h"
#include "MenuState.h"
#include "Utils.h"
#include <stdexcept>
#include <iostream>
#include <time.h>

#define STATE_NUM 2
enum cstate_t {
	GAME = 0,
	ENDMENU = 1
};

SDL_Window* createWindow()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		throw std::runtime_error(SDL_GetError());
	}
	SDL_Window* win = SDL_CreateWindow("CatMove", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
	if (win == 0) {
		throw std::runtime_error(SDL_GetError());
	}
	return win;
}

int main(){
	LOG("New game started");
	int endCause = 0;
	cstate_t CurrentState = GAME;
	SDL_Window* window = createWindow();
	srand(time(NULL));
	while(endCause == 0) {
		IState* catProg;
		switch(CurrentState) {
			case GAME:
				catProg = new SDL_Main(*window);
			break;
			case ENDMENU:
				catProg = new MenuState(*window);
			break;
			default:
				throw std::runtime_error("Bad state");
			break;
		}
		endCause = catProg->EventLoop();
		delete catProg;
		CurrentState = static_cast<cstate_t>( (CurrentState + 1) % STATE_NUM );
	}
	SDL_DestroyWindow(window);
	LOG("User closed game window");
	return 0;
}
