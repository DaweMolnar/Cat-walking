#ifndef MENUSTATE_H
#define MENUSTATE_H
#include "IState.h"
class MenuState:
	public IState
{
	public:
		MenuState(SDL_Window& window);
		~MenuState();
		virtual int EventLoop();
	private:
		unsigned int retCause_;
		SDL_Texture *background_;
		void handleEvents(SDL_Event &e);
		void renderItems();
};
#endif
