#include <stdexcept>
#include "MovingItem.h"

MovingItem::MovingItem(SDL_Renderer &ren, std::string filename) : ren_(ren) {
	texture_ = IMG_LoadTexture(&ren_, filename.c_str());
	if (texture_ == 0) {
		throw std::runtime_error(SDL_GetError());
	}
}
