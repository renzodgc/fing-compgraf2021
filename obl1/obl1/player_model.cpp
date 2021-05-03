// HEADERS
// -----------------------------------------------------------------------------------
#include "player_model.h"
#include <SDL_stdinc.h>
#include <SDL_scancode.h>
#include <SDL_keycode.h>

// NAMESPACE
// -----------------------------------------------------------------------------------
using namespace std;

// METHODS
// -----------------------------------------------------------------------------------

// CONSTANTS
enum class PlayerIs { idle, moving_left, moving_right, moving_down, moving_up };

// GENERIC

Player::Player(position starting_position) {
	player_position = starting_position;
	player_angle = 0.f;
	player_state = PlayerIs::idle;
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

void Player::move_right() {
	if (player_state == PlayerIs::idle) {
		player_state = PlayerIs::moving_right;
		before_movement = player_position;
	}
}

void Player::move_left() {
	if (player_state == PlayerIs::idle) {
		player_state = PlayerIs::moving_left;
		before_movement = player_position;
	}
}

void Player::update(double elapsed_time) {
	switch (player_state) {
	case PlayerIs::moving_left:
		player_position.x += elapsed_time * MOVEMENT_CAMERA_SPEED;
		cout << player_position.x << endl;
		if (player_position.x - before_movement.x >= 1) {
			player_state = PlayerIs::idle;
		}
		break;
	case PlayerIs::moving_right:
		player_position.x -= elapsed_time * MOVEMENT_CAMERA_SPEED;
		cout << player_position.x << endl;
		if (player_position.x - before_movement.x <= -1) {
			player_state = PlayerIs::idle;
		}
		break;
	default:
		break;
	}
}
