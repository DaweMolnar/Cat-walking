#include <iostream>
#include "SDL_Main.h"
#include <time.h>

int main(int argc, char **argv){
	srand(time(NULL));
	SDL_Main catProg;
	catProg.EventLoop();
	return 0;

}