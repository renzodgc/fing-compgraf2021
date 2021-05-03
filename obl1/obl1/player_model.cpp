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
	player_angle = 0.f;
}

position Player::get_player_position() {
	return player_position;
}

float Player::get_player_angle() {
	return player_angle;
}

void Player::set_player_position(position new_position) {
	player_position = new_position;
}

void Player::set_player_angle(float new_angle) {
	player_angle = new_angle;
}
