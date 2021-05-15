// HEADERS
// -----------------------------------------------------------------------------------
#include "game_manager.h"

// NAMESPACE
// -----------------------------------------------------------------------------------
using namespace std;

// METHODS
// -----------------------------------------------------------------------------------

// Constructor and Singleton method
// -----------------------------------------------------------------------------------

Game::Game() {
	this->score = 0;
	this->level = 0;
	this->coins = 0;
	this->lanes = {
		new Grass(4.f),
		new Grass(3.f),
		new Grass(2.f),
		new Grass(1.f),
		new Grass(0.f),
		new Street(-1.f),
		new Street(-2.f),
		new Grass(-3.f),
		new Street(-4.f),
		new Street(-5.f),
		new Grass(-6.f),
		new Grass(-7.f)
	};
}

Game& Game::get_instance() {
	static Game instance; // Guaranteed to be destroyed. Instantiated on first use.
	return instance;
}

// Getters & Setters
// -----------------------------------------------------------------------------------

int Game::getScore() {
	return this->score;
}

int Game::getLevel() {
	return this->level;
}

int Game::getCoins() {
	return this->coins;
}

vector<Lane*> Game::getLanes() {
	return this->lanes;
}

void Game::setScore(int score) {
	this->score = score;
}

void Game::addCoin() {
	this->coins++;
}
