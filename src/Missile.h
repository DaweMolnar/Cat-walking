#pragma once
#include "MovingItem.h"

class Missile : public MovingItem
{
	unsigned int speed_;
	bool finished_;
public:
	Missile(SDL_Renderer &ren, std::string filename, SDL_Rect& destination);
	bool finished() { return finished_; }
	bool isCollide(SDL_Rect& otherDest);
	void boom() { finished_ = true; }
	void move() override;
};

