// HEADERS
// -----------------------------------------------------------------------------------

#include "object.h"

// NAMESPACE
// -----------------------------------------------------------------------------------

using namespace std;

// OBJECT METHODS
// -----------------------------------------------------------------------------------

// Constructors / Destructors
// -----------------------------------------------------------------------------------

Object::Object(unsigned int id, Vector* position, // Main properties
	Color diffuse_color, Color specular_color, // Colors
	float refraction_coef, float transmission_coef, float specular_coef, float diffuse_coef, float ambience_coef, // Coefficients
	bool reflective) { // Flags

	this->id = id;
	this->position = position;
	this->diffuse_color = diffuse_color;
	this->specular_color = specular_color;
	this->refraction_coef = refraction_coef;
	this->transmission_coef = transmission_coef;
	this->specular_coef = specular_coef;
	this->diffuse_coef = diffuse_coef;
	this->ambience_coef = ambience_coef;
	this->reflective = reflective;
}

// Getters & Setters
// -----------------------------------------------------------------------------------

// Main properties
unsigned int Object::get_id() {
	return id;
}
ObjectIs Object::get_type() {
	return type;
}
Vector* Object::get_position() {
	return position;
}

// Colors
Color Object::get_diffuse_color() {
	return diffuse_color;
}
Color Object::get_specular_color() {
	return specular_color;
}

// Coefficients
float Object::get_refraction_coef() {
	return refraction_coef;
}
float Object::get_transmission_coef() {
	return transmission_coef;
}
float Object::get_specular_coef() {
	return specular_coef;
}
float Object::get_diffuse_coef() {
	return diffuse_coef;
}
float Object::get_ambience_coef() {
	return ambience_coef;
}

// Flags
bool Object::is_opaque() {
	return transmission_coef == 1.f;
}
bool Object::is_reflective() {
	return reflective;
}

// Aux Methods
// -----------------------------------------------------------------------------------

ObjectIs Object::parse_object_type(string type) {
	
	ObjectIs result = ObjectIs::Sphere;

	if (type == "triangle_mesh") {
		result = ObjectIs::TriangleMesh;
	} 
	else if (type == "sphere") {
		result = ObjectIs::Sphere;
	}
	else if (type == "cylinder") {
		result = ObjectIs::Cylinder;
	}
	else if (type == "rectangle") {
		result = ObjectIs::Rectangle;
	}

	return result;
}
