#include <iostream>
#include <stdexcept>
#include "SDL_Main.h"
#include "Utils.h"
#include <time.h>

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
	SDL_Window* window = createWindow();
	srand(time(NULL));
	while(endCause == 0) {
		SDL_Main* catProg = new SDL_Main(*window);
		endCause = catProg->EventLoop();
		delete catProg;
	}
	SDL_DestroyWindow(window);
	LOG("User closed game window");
	return 0;

}
