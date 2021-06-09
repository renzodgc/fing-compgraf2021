// HEADERS
// -----------------------------------------------------------------------------------

#include "camera.h"

// METHODS
// -----------------------------------------------------------------------------------

// Constructors / Destructors
// -----------------------------------------------------------------------------------

Camera::Camera(Vector position, pair<int, int> size) {
	this->position = position;
	this->size = size;
}

// Getters & Setters
// -----------------------------------------------------------------------------------

Vector Camera::get_position() {
	return this->position;
}

pair<int, int> Camera::get_size() {
	return this->size;
}

// Main Methods
// -----------------------------------------------------------------------------------
