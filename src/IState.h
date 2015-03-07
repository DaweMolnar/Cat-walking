#ifndef BASESTATE_H
#define BASESTATE_H
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdexcept>
class IState {
public:
	virtual ~IState() {}
	IState(SDL_Window& window); 
	virtual int EventLoop() = 0;
protected:
	SDL_Renderer *ren_;
	TTF_Font* font_;
	bool run_;
	SDL_Window& win_;
	void renderText(const SDL_Color& color,SDL_Rect& destination, const std::string& text);
};

#endif
