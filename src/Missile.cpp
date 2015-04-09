#include "Missile.h"
#include <time.h>

#define SECTION_WIDTH 32
#define SECTION_HEIGHT 32

Missile::Missile(SDL_Renderer &ren, std::string filename, SDL_Rect& destination):
MovingItem(ren,filename)
{
	currentDirection_ = LEFT;
	finished_ = false;
	section_.x = 0;
	section_.y = 0;
	section_.w = SECTION_WIDTH;
	section_.h = SECTION_HEIGHT;

	speed_ = rand() % 10 + 10;
	destination_ = destination;
	destination_.w = SECTION_WIDTH;
	destination_.h = SECTION_HEIGHT;
}

void
Missile::move()
{
	if (destination_.y > 0) {
		destination_.y = destination_.y - speed_;
	}
	else {
		finished_ = true;
	}
}
