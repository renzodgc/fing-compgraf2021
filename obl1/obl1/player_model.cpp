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
		player_angle = 270.f;
	}
}

void Player::move_left() {
	if (player_state == PlayerIs::idle) {
		player_state = PlayerIs::moving_left;
		before_movement = player_position;
		player_angle = 90.f;
	}
}

void Player::move_up() {
	if (player_state == PlayerIs::idle) {
		player_state = PlayerIs::moving_up;
		before_movement = player_position;
		player_angle = 0.f;
	}
}

void Player::move_down() {
	if (player_state == PlayerIs::idle) {
		player_state = PlayerIs::moving_down;
		before_movement = player_position;
		player_angle = 180.f;
	}
}


void Player::update(double elapsed_time) {
	switch (player_state) {
	case PlayerIs::moving_right:
		player_position.x = min(before_movement.x + 1.0, player_position.x + elapsed_time * PLAYER_SPEED);
		if (player_position.x - before_movement.x >= 1) {
			player_state = PlayerIs::idle;
		}
		break;
	case PlayerIs::moving_left:
		player_position.x = max(before_movement.x - 1.0, player_position.x - elapsed_time * PLAYER_SPEED);
		if (player_position.x - before_movement.x <= -1) {
			player_state = PlayerIs::idle;
		}
		break;
	case PlayerIs::moving_down:
		player_position.z = min(before_movement.z + 1.0, player_position.z + elapsed_time * PLAYER_SPEED);
		if (player_position.z - before_movement.z >= 1) {
			player_state = PlayerIs::idle;
		}
		break;
	case PlayerIs::moving_up:
		player_position.z = max(before_movement.z - 1.0, player_position.z - elapsed_time * PLAYER_SPEED);
		if (player_position.z - before_movement.z <= -1) {
			player_state = PlayerIs::idle;
		}
		break;
	}
}

void Player::draw() {
	glPushMatrix();

	glTranslatef(player_position.x, player_position.y, player_position.z);
	glRotatef(player_angle, 0.f, 1.f, 0.f);

	DrawCube();

	glPopMatrix();
}
