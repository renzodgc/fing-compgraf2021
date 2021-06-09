// HEADERS
// -----------------------------------------------------------------------------------

#include "light.h"

// METHODS
// -----------------------------------------------------------------------------------

// Constructors / Destructors
// -----------------------------------------------------------------------------------

Light::Light(Vector* position, Color color) {
	this->position = position;
	this->color = color;
}

// Getters & Setters
// -----------------------------------------------------------------------------------

Vector* Light::get_position() {
	return this->position;
}

Color Light::get_color() {
	return this->color;
}

// Main Methods
// -----------------------------------------------------------------------------------
