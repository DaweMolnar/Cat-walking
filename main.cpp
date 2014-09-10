#include <iostream>
#include "SDL_Main.h"
#include <time.h>

int main(){
	srand(time(NULL));
	SDL_Main catProg;
	catProg.EventLoop();
	return 0;

}
