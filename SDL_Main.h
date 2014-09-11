#pragma once
#include "Character.h"
#include "Enemy.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <vector>

class SDL_Main
{
	bool run_;
	unsigned int score_;
	unsigned int retCause_;
	SDL_Window *win_;
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
	SDL_Main();
	~SDL_Main();
	int EventLoop();
	bool run() { return run_; }
};

