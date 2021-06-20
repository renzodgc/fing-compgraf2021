// HEADERS
// -----------------------------------------------------------------------------------

#include "camera.h"

// METHODS
// -----------------------------------------------------------------------------------

// Constructors / Destructors
// -----------------------------------------------------------------------------------

Camera::Camera(Vector position, Vector window_position) {
	this->position = position;
	this->window_position = window_position;
}

// Getters & Setters
// -----------------------------------------------------------------------------------

Vector Camera::get_position() {
	return this->position;
}
void Camera::set_position(Vector position) {
	this->position = position;
}

Vector Camera::get_window_position() {
	return this->window_position;
}
void Camera::set_window_position(Vector window_position) {
	this->window_position = window_position;
}
