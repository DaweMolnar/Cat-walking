#pragma once
#include "MovingItem.h"

class Enemy :
	public MovingItem
{
	unsigned int speed_;
	bool finished_;
public:
	Enemy(SDL_Renderer &ren, std::string filename);
	~Enemy() {}
	bool finished() { return finished_; }
	bool isCollide(SDL_Rect& otherDest);
	void move();
};

