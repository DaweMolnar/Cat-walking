#pragma once
#include "IState.h"
#include "Character.h"
#include "Enemy.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <vector>

class SDL_Main:
	public IState
{
	unsigned int score_;
	unsigned int retCause_;
	SDL_Renderer *ren_;
	SDL_Texture *background_;
	Character* catChar_;
	TTF_Font* font_;
	std::vector<Enemy*> enemyList_;

	void printScore();
	void handleEvents(SDL_Event &e);
	void renderItems();
	void moveItems();
	void addNewEnemies();
public:
	SDL_Main(SDL_Window& window);
	~SDL_Main();
	virtual int EventLoop();
	bool run() { return run_; }
};

