#include <iostream>
#include "SDL_Main.h"
#include "Utils.h"
#include <time.h>

int main(){
	LOG("New game started");
	int endCause = 0;
	srand(time(NULL));
	while(endCause == 0) {
		SDL_Main catProg;
		endCause = catProg.EventLoop();
	}
	LOG("User closed game window");
	return 0;

}
