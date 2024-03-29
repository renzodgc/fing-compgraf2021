// HEADERS
// -----------------------------------------------------------------------------------
#include "player_model.h"

// NAMESPACE
// -----------------------------------------------------------------------------------
using namespace std;

// METHODS
// -----------------------------------------------------------------------------------

// Constructor and Singleton method
// -----------------------------------------------------------------------------------

Player::Player() {
	player_position = { 0.f, 0.f, 0.f };
	player_angle = 0.f;
	player_state = PlayerIs::idle;
	is_bouncing = false;
	vertically_ascending = false;
	vertically_descending = false;

	draw_manager = &Draw::get_instance();
}

Player& Player::get_instance() {
	static Player instance; // Guaranteed to be destroyed. Instantiated on first use.
	return instance;
}

// Getters & Setters
// -----------------------------------------------------------------------------------

Vector3 Player::get_player_position() {
	return player_position;
}

float Player::get_player_angle() {
	return player_angle;
}

void Player::set_player_position(Vector3 new_position) {
	player_position = new_position;
}

void Player::set_player_angle(float new_angle) {
	player_angle = new_angle;
}

// Main methods
// -----------------------------------------------------------------------------------

void Player::update(double elapsed_time) {
	switch (player_state) {
	case PlayerIs::moving_right:
		player_position.x = min(before_movement.x + 1.0f, player_position.x + (float)(elapsed_time * PLAYER_SPEED));
		if (player_position.x - before_movement.x >= 1) {
			player_state = PlayerIs::idle;
		}
		break;
	case PlayerIs::moving_left:
		player_position.x = max(before_movement.x - 1.0f, player_position.x - (float)(elapsed_time * PLAYER_SPEED));
		if (player_position.x - before_movement.x <= -1) {
			player_state = PlayerIs::idle;
		}
		break;
	case PlayerIs::moving_down:
		player_position.z = min(before_movement.z + 1.0f, player_position.z + (float)(elapsed_time * PLAYER_SPEED));
		if (player_position.z - before_movement.z >= 1) {
			player_state = PlayerIs::idle;
		}
		break;
	case PlayerIs::moving_up:
		player_position.z = max(before_movement.z - 1.0f, player_position.z - (float)(elapsed_time * PLAYER_SPEED));
		if (player_position.z - before_movement.z <= -1) {
			player_state = PlayerIs::idle;
		}
		break;
	case PlayerIs::idle:
		is_bouncing = false;
		break;
	}
	// Translate and scale player vertically
	if (vertically_ascending) {
		player_position.y = min(PLAYER_MAX_HEIGHT, player_position.y + (PLAYER_MAX_HEIGHT * (float)(PLAYER_SPEED * elapsed_time)));
		if (player_position.y == PLAYER_MAX_HEIGHT) {
			vertically_ascending = false;
			vertically_descending = true;
		}
	} else {
		if (vertically_descending) {
			player_position.y = max(0.f, player_position.y - (PLAYER_MAX_HEIGHT * (float)(PLAYER_SPEED * elapsed_time)));
			if (player_position.y == 0.f) vertically_descending = false;
		}
	}
}

void Player::draw(bool use_texture) {
	glPushMatrix();

	glTranslatef(player_position.x, player_position.y, player_position.z);
	glRotatef(player_angle, 0.f, 1.f, 0.f);
	glScalef(1.f, (0.3f * player_position.y) + 1.f, 1.f);

	draw_manager->player(use_texture);

	glPopMatrix();
}

// Motion methods
// -----------------------------------------------------------------------------------

void Player::move_right() {
	if (player_state == PlayerIs::idle && !is_bouncing) {
		player_state = PlayerIs::moving_right;
		before_movement = player_position;
		player_angle = 270.f;
		vertically_ascending = true;
	}
}

void Player::move_left() {
	if (player_state == PlayerIs::idle && !is_bouncing) {
		player_state = PlayerIs::moving_left;
		before_movement = player_position;
		player_angle = 90.f;
		vertically_ascending = true;
	}
}

void Player::move_up() {
	if (player_state == PlayerIs::idle && !is_bouncing) {
		player_state = PlayerIs::moving_up;
		before_movement = player_position;
		player_angle = 0.f;
		vertically_ascending = true;
	}
}

void Player::move_down() {
	if (player_state == PlayerIs::idle && !is_bouncing) {
		player_state = PlayerIs::moving_down;
		before_movement = player_position;
		player_angle = 180.f;
		vertically_ascending = true;
	}
}

void Player::bounce_back() {
	if (!is_bouncing) {
		is_bouncing = true;
		switch (player_state) {
		case PlayerIs::moving_right:
			player_state = PlayerIs::moving_left;
			before_movement = { before_movement.x + 1, before_movement.y, before_movement.z };
			break;
		case PlayerIs::moving_left:
			player_state = PlayerIs::moving_right;
			before_movement = { before_movement.x - 1, before_movement.y, before_movement.z };
			break;
		case PlayerIs::moving_down:
			player_state = PlayerIs::moving_up;
			before_movement = { before_movement.x, before_movement.y, before_movement.z + 1 };
			break;
		case PlayerIs::moving_up:
			player_state = PlayerIs::moving_down;
			before_movement = { before_movement.x, before_movement.y, before_movement.z - 1 };
			break;
		}
	}
	
}
