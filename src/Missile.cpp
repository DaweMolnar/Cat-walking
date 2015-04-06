#include "Missile.h"
#include <time.h>

#define SECTION_WIDTH 20
#define SECTION_HEIGHT 20

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
}

bool
Missile::isCollide(SDL_Rect& otherDest)
{
	//Axis-Aligned Bounding Box
	if (otherDest.x < destination_.x + destination_.w &&
		otherDest.x + otherDest.w > destination_.x &&
		otherDest.y < destination_.y + destination_.h &&
		otherDest.h + otherDest.y > destination_.y) {
		// collision detected!
		return true;
	}
	return false;
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
