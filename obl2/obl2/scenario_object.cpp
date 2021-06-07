// HEADERS
// -----------------------------------------------------------------------------------

#include "scenario_object.h"

// METHODS
// -----------------------------------------------------------------------------------

// Constructors / Destructors
// -----------------------------------------------------------------------------------
ScenarioObject::ScenarioObject(Vector centre_position, Color color, float transparency, float refraction_coef, bool reflective) {
	this->centre_position = centre_position;
	this->color = color;
	this->transparency = transparency;
	this->refraction_coef = refraction_coef;
	this->reflective = reflective;
}

// Getters & Setters
// -----------------------------------------------------------------------------------
ObjectIs ScenarioObject::get_type() {
	return type;
}

Vector ScenarioObject::get_centre_position() {
	return centre_position;
}

Color ScenarioObject::get_color() {
	return color;
}

float ScenarioObject::get_transparency() {
	return transparency;
}

float ScenarioObject::get_refraction_coef() {
	return refraction_coef;
}

bool ScenarioObject::get_reflective() {
	return reflective;
}

// Main Methods
// -----------------------------------------------------------------------------------
