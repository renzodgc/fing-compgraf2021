// HEADERS
// -----------------------------------------------------------------------------------
#include "player_model.h"

// NAMESPACE
// -----------------------------------------------------------------------------------
using namespace std;

// METHODS
// -----------------------------------------------------------------------------------

// GENERIC

Player::Player(position starting_position) {
	player_position = starting_position;
}

position Player::get_player_position() {
	return player_position;
}

void Player::set_player_position(position new_position) {
	player_position = new_position;
}
