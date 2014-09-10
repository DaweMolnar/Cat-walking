#include <iostream>
#include "SDL_Main.h"
#include "Utils.h"
#include <time.h>

int main(){
	LOG("New game started");
	srand(time(NULL));
	SDL_Main catProg;
	catProg.EventLoop();
	return 0;

}
