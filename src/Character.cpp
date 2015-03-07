#include "Character.h"
#include <errno.h>

#define STEP_SIZE 10
#define SECTION_WIDTH 32
#define SECTION_HEIGHT 32
#define SPRITE_MAX 128
#define COLUMN_DOWN 0
#define COLUMN_LEFT 1
#define COLUMN_RIGHT 2
#define COLUMN_UP 3

Character::Character(SDL_Renderer &ren, std::string filename):
MovingItem(ren,filename)
{
	currentDirection_ = LEFT;
	section_.x = 0;
	section_.y = COLUMN_LEFT * SECTION_HEIGHT;
	section_.w = SECTION_WIDTH;
	section_.h = SECTION_HEIGHT;

	destination_.x = WINDOW_HEIGHT;
	destination_.y = LAND_POS;
	destination_.w = SECTION_WIDTH*2;
	destination_.h = SECTION_HEIGHT*2;
}

void
Character::move()
{
	if (currentDirection_ == LEFT) { moveLeft(); }
	else if(currentDirection_ == RIGHT ){ moveRight(); }
	else if (currentDirection_ == UP){ moveUp(); }
	else if (currentDirection_ == DOWN){ moveDown(); }
}

void
Character::moveLeft()
{
	section_.y = COLUMN_LEFT * SECTION_HEIGHT;
	section_.x = (section_.x + SECTION_WIDTH) % SPRITE_MAX;
	destination_.x = destination_.x - STEP_SIZE;
	if (destination_.x < 0) {
		destination_.x = WINDOW_WIDTH;
	}
}

void
Character::moveRight()
{
	section_.y = COLUMN_RIGHT * SECTION_HEIGHT;
	section_.x = (section_.x + SECTION_WIDTH) % SPRITE_MAX;
	destination_.x = destination_.x + STEP_SIZE;
	if (destination_.x > WINDOW_WIDTH) {
		destination_.x = 0;
	}
}

void
Character::moveUp()
{
	section_.y = COLUMN_UP * SECTION_HEIGHT;
	section_.x = (section_.x + SECTION_WIDTH) % SPRITE_MAX;
	if (destination_.y > LAND_POS) {
		destination_.y = destination_.y - STEP_SIZE;
	}
}

void
Character::moveDown()
{
	section_.y = COLUMN_DOWN * SECTION_HEIGHT;
	section_.x = (section_.x + SECTION_WIDTH) % SPRITE_MAX;
	if (destination_.y < WINDOW_HEIGHT - 2*SECTION_HEIGHT) {
		destination_.y = destination_.y + STEP_SIZE;
	}
}

Character::~Character()
{
}
