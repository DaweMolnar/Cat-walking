#pragma once
#include "IState.h"
#include "Character.h"
#include "Enemy.h"
#include "Missile.h"
#include <SDL.h>
#include <vector>

class GameState:
	public IState
{
	unsigned int score_;
	unsigned int retCause_;
	SDL_Texture *background_;
	Character* catChar_;
	std::vector<Enemy*> enemyList_;
	std::vector<Missile*> shotList_;
	time_t shotTime_; 

	void printScore();
	void handleEvents(SDL_Event &e);
	void renderItems();
	void moveItems();
	void addNewEnemies();
	void shot(SDL_Rect& rect);
	bool missileCollision(Missile* missile);
public:
	GameState(SDL_Window& window);
	~GameState();
	virtual int EventLoop();
	bool run() { return run_; }
};

