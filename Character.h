#pragma once
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "MovingItem.h"
class Character:
	public MovingItem
{
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();

public:
	Character(SDL_Renderer &ren, std::string filename);
	~Character();

	virtual void move();
	void turnLeft() { currentDirection_ = LEFT; }
	void turnRight() { currentDirection_ = RIGHT; }
	void turnUp() { currentDirection_ = UP; }
	void turnDown() { currentDirection_ = DOWN; }
};

