// HEADERS
// -----------------------------------------------------------------------------------

#include "scenario_object.h"

// METHODS
// -----------------------------------------------------------------------------------

// Constructors / Destructors
// -----------------------------------------------------------------------------------
ScenarioObject::ScenarioObject(short id, Vector centre_position, Color diffuse_color, Color specular_color, float transparency, float refraction_coef, bool reflective) {
	this->id = id;
	this->centre_position = centre_position;
	this->diffuse_color = diffuse_color;
	this->specular_color = specular_color;
	this->transparency = transparency;
	this->refraction_coef = refraction_coef;
	this->reflective = reflective;
}

// Getters & Setters
// -----------------------------------------------------------------------------------
short ScenarioObject::get_id() {
	return id;
}

ObjectIs ScenarioObject::get_type() {
	return type;
}

Vector ScenarioObject::get_centre_position() {
	return centre_position;
}

Color ScenarioObject::get_diffuse_color() {
	return diffuse_color;
}

Color ScenarioObject::get_specular_color() {
	return diffuse_color;
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
