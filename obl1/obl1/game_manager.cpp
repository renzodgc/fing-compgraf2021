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
	this->level = 1;
	this->coins = 0;
	this->lanes = generateBaseLanes();
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

// Aux methods
// -----------------------------------------------------------------------------------

vector<Lane*> Game::generateBaseLanes() {

	// Generate lanes vector with back wall
	vector<Lane*> lanes = { new Wall((float)INITIAL_LANES_INTERVAL) };

	// Generate first INITIAL_LANES_INTERVAL lanes, always as PLANE grass
	for (int i = 1; i < INITIAL_LANES_INTERVAL * 2; i++) {
		lanes.push_back(new Grass((float)(INITIAL_LANES_INTERVAL - i)));
	}

	// Generate first LANES_INTERVAL lanes, after the initial ones, using the random way
	for (int i = 0; i < LANES_INTERVAL; i++) {
		lanes.push_back(addLane((float)(-INITIAL_LANES_INTERVAL - i)));
	}

	return lanes;
}

Lane* Game::addLane(float position) {
	
	Lane* lane{};

	if (grass_in_a_row >= (MAX_GRASS_COEF * this->level)) {
		lane = new Grass(position);
		this->grass_in_a_row = 0;
	}
	else if (street_in_a_row >= (MAX_STREET_COEF * this->level)) {
		lane = new Street(position);
		this->street_in_a_row = 0;
	}
	else {
		LaneIs laneType = LaneIs(get_random(LANE_TYPES));
		switch (laneType) {
		case LaneIs::wall: // Don't want walls so we treat them like grass
		case LaneIs::grass:
			lane = new Grass(position);
			this->grass_in_a_row++;
			break;
		case LaneIs::street:
			lane = new Street(position);
			this->street_in_a_row++;
			break;
		}
	}

	return lane;
}

void Game::removeLane() {

	Lane* lane{};

}




