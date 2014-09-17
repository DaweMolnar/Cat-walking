#ifndef BASESTATE_H
#define BASESTATE_H
#include <SDL.h>

class IState {
public:
	virtual ~IState() {}
	IState(SDL_Window& window) : run_(true), win_(window) {}
	virtual int EventLoop() = 0;
protected:
	bool run_;
	SDL_Window& win_;
};

#endif
