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

Object::Object(unsigned int id, Vector* position, Color color, float transparency, float refraction_coef, bool reflective) {
	this->id = id;
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

unsigned int Object::get_id() {
	return id;
}

Vector* Object::get_position() {
	return position;
}

Color Object::get_color() {
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

// Aux Methods
// -----------------------------------------------------------------------------------

ObjectIs Object::parse_object_type(string type) {
	
	ObjectIs result;

	if (type == "triangle_mesh") {
		result = ObjectIs::TriangleMesh;
	} 
	else if (type == "sphere") {
		result = ObjectIs::Sphere;
	}
	else if (type == "cillinder") {
		result = ObjectIs::Cillinder;
	}
	else if (type == "rectangle") {
		result = ObjectIs::Rectangle;
	}

	return result;
}

// SPHERE METHODS
// -----------------------------------------------------------------------------------

// Constructors / Destructors
// -----------------------------------------------------------------------------------

Sphere::Sphere(unsigned int id, Vector* position, Color color, float transparency, float refraction_coef, bool reflective) : Object(id, position, color, transparency, refraction_coef, reflective) {
	this->type = ObjectIs::Sphere;
}