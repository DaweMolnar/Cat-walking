#pragma once
#include <string>
#include <SDL.h>
#include <SDL_image.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define LAND_POS 336

class MovingItem
{
protected:
	enum Direction{
		LEFT, RIGHT, UP, DOWN
	} currentDirection_;
	SDL_Texture *texture_;
	SDL_Renderer &ren_;
	SDL_Rect section_;
	SDL_Rect destination_;
public:
	MovingItem(SDL_Renderer &ren, std::string filename);
	virtual ~MovingItem() {}
	virtual void move() = 0;
	virtual SDL_Texture* getTexture() { return texture_; }
	virtual SDL_Rect& getSection() { return section_; }
	virtual SDL_Rect& getDestination() { return destination_; }
};

