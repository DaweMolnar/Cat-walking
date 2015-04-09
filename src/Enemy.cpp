#include "Enemy.h"
#include <time.h>

#define SECTION_WIDTH 32
#define SECTION_HEIGHT 32

Enemy::Enemy(SDL_Renderer &ren, std::string filename):
MovingItem(ren,filename)
{
	currentDirection_ = LEFT;
	finished_ = false;
	section_.x = 0;
	section_.y = 0;
	section_.w = SECTION_WIDTH;
	section_.h = SECTION_HEIGHT;

	speed_ = rand() % 10 + 10;
	destination_.x = rand() % (WINDOW_WIDTH - 2 * SECTION_HEIGHT);
	destination_.y = 0;
	destination_.w = SECTION_WIDTH;
	destination_.h = SECTION_HEIGHT;
}

bool
Enemy::isCollide(SDL_Rect& otherDest)
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
Enemy::move()
{
	if (destination_.y < WINDOW_HEIGHT - 2 * SECTION_HEIGHT) {
		destination_.y = destination_.y + speed_;
	}
	else {
		finished_ = true;
	}
}
