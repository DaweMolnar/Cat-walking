#include "SDL_Main.h"
#include <iostream>
#include <errno.h>
#include <algorithm>
#include <stdexcept>
#define MAX_ENEMY 5

SDL_Main::SDL_Main()
	: run_(true),
	score_(0)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		throw std::runtime_error(SDL_GetError());
	}
	win_= SDL_CreateWindow("CatMove", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
	if (win_ == 0) {
		throw std::runtime_error(SDL_GetError());
	}
	ren_ = SDL_CreateRenderer(win_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren_ == 0) {
		throw std::runtime_error(SDL_GetError());
	}
	background_ = IMG_LoadTexture(ren_, "Sprites/background.png");
	if (background_ == 0) {
		throw std::runtime_error(SDL_GetError());
	}
	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
		throw std::runtime_error(SDL_GetError());
	}
	TTF_Init();
	font_ = TTF_OpenFont("sample.ttf", 20);
	catChar_ = new Character(*ren_, "Sprites/catsheet.png");
	addNewEnemies();
}

void
SDL_Main::printScore()
{
	SDL_Color color = { 255, 255, 255, 255 };
	std::string scoreText("Score: " + std::to_string(score_));
	SDL_Surface *surf = TTF_RenderText_Blended(font_, scoreText.c_str(), color);
	SDL_Texture* score = SDL_CreateTextureFromSurface(ren_, surf);
	SDL_FreeSurface(surf);
	SDL_Rect destination;
	destination.x = 20;
	destination.y = 20;
	SDL_QueryTexture(score, NULL, NULL, &destination.w, &destination.h);
	SDL_RenderCopy(ren_, score, NULL, &destination);
}

void
SDL_Main::handleEvents(SDL_Event &e)
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
		break;
	case SDL_QUIT:
		run_ = false;
		break;
	default:
		run_ = true;
		break;
	}
}
bool isEnemyFinished(Enemy* e)
{
	return e->finished();
}
void
SDL_Main::addNewEnemies()
{
	for (unsigned int i = enemyList_.size(); i < MAX_ENEMY; i++) {
		enemyList_.push_back(new Enemy(*ren_, "Sprites/faller.png"));
	}
}
void
SDL_Main::moveItems()
{
	catChar_->move();
	for (unsigned int i = 0; i < enemyList_.size(); i++) {
		enemyList_[i]->move();
		if (enemyList_[i]->finished()) {
			score_ += 10;
		}
		SDL_Rect rect = catChar_->getDestination();
		if (enemyList_[i]->isCollide(rect)) {
			run_ = false;
		}
	}
	enemyList_.erase(std::remove_if(std::begin(enemyList_), std::end(enemyList_), isEnemyFinished), std::end(enemyList_));
	addNewEnemies();
}

void
SDL_Main::renderItems()
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
	printScore();
	SDL_RenderPresent(ren_);
}

void
SDL_Main::EventLoop()
{
	while (run_) {
		moveItems();
		renderItems();
		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			handleEvents(e);
		}
		SDL_Delay(200);
	}
}

SDL_Main::~SDL_Main()
{
}
