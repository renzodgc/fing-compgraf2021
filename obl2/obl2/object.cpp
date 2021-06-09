// HEADERS
// -----------------------------------------------------------------------------------

#include "object.h"

// METHODS
// -----------------------------------------------------------------------------------

// Constructors / Destructors
// -----------------------------------------------------------------------------------

Object::Object(Vector* position, Color* color, float transparency, float refraction_coef, bool reflective) {
	this->position = position;
	this->color = color;
	this->transparency = transparency;
	this->refraction_coef = refraction_coef;
	this->reflective = reflective;
}

// Getters & Setters
// -----------------------------------------------------------------------------------

ObjectIs Object::get_type() {
	return type;
}

Vector* Object::get_position() {
	return position;
}

Color* Object::get_color() {
	return color;
}

float Object::get_transparency() {
	return transparency;
}

float Object::get_refraction_coef() {
	return refraction_coef;
}

bool Object::get_reflective() {
	return reflective;
}

// Main Methods
// -----------------------------------------------------------------------------------
