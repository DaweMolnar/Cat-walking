#include "GameState.h"
#include <iostream>
#include <errno.h>
#include <algorithm>
#include <stdexcept>
#include "Utils.h"
#define MAX_ENEMY 5
#define RELOAD_TIME 0.1

GameState::GameState(SDL_Window& window)
	: 
	IState(window),
	score_(0),
	retCause_(0)
{
	shotTime_=time(0);
	background_ = IMG_LoadTexture(ren_, "Sprites/background.png");
	if (background_ == 0) {
		throw std::runtime_error(SDL_GetError());
	}

	font_ = TTF_OpenFont("sample.ttf", 20);
	catChar_ = new Character(*ren_, "Sprites/catsheet.png");
	addNewEnemies();
}

void
GameState::printScore()
{
	SDL_Color color = { 255, 255, 255, 255 };
	std::string scoreText("Score: " + std::to_string(score_));
	SDL_Rect destination;
	destination.x = 20;
	destination.y = 20;
	renderText(color,destination,scoreText);
}

void
GameState::handleEvents(SDL_Event &e)
{
	switch (e.type) {
	case SDL_KEYDOWN:
		if (e.key.keysym.sym == SDLK_LEFT)
			catChar_->turnLeft();
		else if (e.key.keysym.sym == SDLK_RIGHT)
			catChar_->turnRight();
		else if (e.key.keysym.sym == SDLK_UP)
			catChar_->turnUp();
		else if (e.key.keysym.sym == SDLK_DOWN)
			catChar_->turnDown();
		else if (e.key.keysym.sym == SDLK_SPACE)
			shot(catChar_->getDestination());
		break;
	case SDL_QUIT:
		retCause_ = -1;
		run_ = false;
		break;
	default:
		run_ = true;
		break;
	}
}
void GameState::shot(SDL_Rect& rect)
{
//	time_t currTime = time(0);
//	if(difftime(currTime,shotTime_) > RELOAD_TIME) {
		shotList_.push_back(new Missile(*ren_, "Sprites/rocket_ship.png", rect));
//		shotTime_=time(0);
//	}
}

bool isEnemyFinished(Enemy* e)
{
	return e->finished();
}


bool isMissileFinished(Missile* e)
{
	return e->finished();
}

void
GameState::addNewEnemies()
{
	for (unsigned int i = enemyList_.size(); i < MAX_ENEMY; i++) {
		enemyList_.push_back(new Enemy(*ren_, "Sprites/gromit.png"));
	}
}

bool
GameState::missileCollision(Missile* missile)
{
	std::size_t pos = 0;
	for(auto enemy : enemyList_) {
		if(enemy->isCollide(missile->getDestination())) {
			score_+=10;
			break;
		}
		pos++;
	}
	if(pos!=enemyList_.size()) {enemyList_.erase(enemyList_.begin()+pos); return true;}
	return false;
}

void
GameState::moveItems()
{
	catChar_->move();
	for (unsigned int i = 0; i < enemyList_.size(); i++) {
		enemyList_[i]->move();
		SDL_Rect rect = catChar_->getDestination();
		if (enemyList_[i]->isCollide(rect)) {
			LOG("Game ended with score : " + std::to_string(score_));
			run_ = false;
		}
	}
	for (unsigned int i = 0; i < shotList_.size(); i++) {
		shotList_[i]->move();
		if(missileCollision(shotList_[i])) shotList_[i]->boom();
	}
	enemyList_.erase(std::remove_if(std::begin(enemyList_), std::end(enemyList_), isEnemyFinished), std::end(enemyList_));
	shotList_.erase(std::remove_if(std::begin(shotList_), std::end(shotList_), isMissileFinished), std::end(shotList_));
	
	addNewEnemies();
}

void
GameState::renderItems()
{
	SDL_RenderClear(ren_);
	SDL_RenderCopy(ren_, background_, NULL, NULL);
	SDL_Rect sect = catChar_->getSection();
	SDL_Texture* text = catChar_->getTexture();
	SDL_Rect dest = catChar_->getDestination();
	SDL_RenderCopy(ren_, text, &sect, &dest);
	for (unsigned int i = 0; i < enemyList_.size(); i++) {
		SDL_RenderCopy(ren_, enemyList_[i]->getTexture(), &enemyList_[i]->getSection(), &enemyList_[i]->getDestination());
	}
	for (unsigned int i = 0; i < shotList_.size(); i++) {
		SDL_RenderCopy(ren_, shotList_[i]->getTexture(), &shotList_[i]->getSection(), &shotList_[i]->getDestination());
	}
	printScore();
	SDL_RenderPresent(ren_);
}

int
GameState::EventLoop()
{
	while (run_) {
		moveItems();
		renderItems();
		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			handleEvents(e);
		}
		SDL_Delay(50);
	}
	return retCause_;
}

GameState::~GameState()
{
	SDL_DestroyRenderer(ren_);
}
