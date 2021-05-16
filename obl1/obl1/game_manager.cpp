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
	if (this->score >= (this->level * (int)LEVEL_RAISE_COEF)) {
		this->level++;
	}
}

void Game::addCoin() {
	this->coins++;
}

// Aux methods
// -----------------------------------------------------------------------------------

void Game::update(float player_position) {

	// Only create new lanes if upper limit is passed
	if (player_position <= this->upper_lane_limit + LANES_INTERVAL) {

		// Create new LANES_INTERVAL lanes
		for (int i = 0; i < LANES_INTERVAL; i++) {
			this->lanes.push_back(addLane((float)(upper_lane_limit - i)));
		}

		// Delete old LANES_INTERVAL lanes:
		
		// Apply lane_deleter to each element (to free their memory)
		for_each(this->lanes.begin(), this->lanes.begin() + LANES_INTERVAL, lane_deleter());
		// Delete null elements
		this->lanes.erase(this->lanes.begin(), this->lanes.begin() + LANES_INTERVAL);

		// Update limits
		this->upper_lane_limit -= LANES_INTERVAL;
		this->lower_lane_limit -= LANES_INTERVAL - 1;

		// Insert wall
		this->lanes.insert(this->lanes.begin(), new Wall((float)this->lower_lane_limit));

	}

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

	// Set counters at 0
	this->grass_in_a_row = 0;
	this->street_in_a_row = 0;

	// Generate first LANES_INTERVAL lanes, after the initial ones, using the random way
	for (int i = 0; i < LANES_INTERVAL; i++) {
		lanes.push_back(addLane((float)(-INITIAL_LANES_INTERVAL - i)));
	}

	// Set limits
	this->upper_lane_limit = -(INITIAL_LANES_INTERVAL + LANES_INTERVAL);
	this->lower_lane_limit = INITIAL_LANES_INTERVAL;

	return lanes;
}

Lane* Game::addLane(float position) {
	
	Lane* lane{};

	// If too many grasses in a row, create street and reset counter
	if (grass_in_a_row >= MAX_GRASS_COEF) {
		lane = new Street(position);
		this->street_in_a_row++;
		this->grass_in_a_row = 0;
	}
	// If too many streets in a row, create grass and reset counter
	else if (street_in_a_row >= (MAX_STREET_COEF * this->level)) {
		lane = new Grass(position);
		this->grass_in_a_row++;
		this->street_in_a_row = 0;
	}
	// If max coefficients are not passed, pick randomly
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

