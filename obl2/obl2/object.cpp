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

Object::Object(unsigned int id, Vector* position, Color diffuse_color, Color specular_color, float refraction_coef, float transmission_coef, float specular_coef, float diffuse_coef, float ambience_coef, bool reflective) {
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

ObjectIs Object::get_type() {
	return type;
}

unsigned int Object::get_id() {
	return id;
}

Vector* Object::get_position() {
	return position;
}

Color Object::get_diffuse_color() {
	return diffuse_color;
}

Color Object::get_specular_color() {
	return specular_color;
}

bool Object::is_opaque() {
	return transmission_coef == 1.f;
}

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

bool Object::is_reflective() {
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

Sphere::Sphere(unsigned int id, Vector* position, Color diffuse_color, Color specular_color, float refraction_coef, float transmission_coef, float specular_coef, float diffuse_coef, float ambience_coef, bool reflective, float radius) : Object(id, position, diffuse_color, specular_color, refraction_coef, transmission_coef, specular_coef, diffuse_coef, ambience_coef, reflective) {
	this->type = ObjectIs::Sphere;
	this->radius = radius;
}

// Reference: https://math.stackexchange.com/questions/1939423/calculate-if-vector-intersects-sphere
// Solve quadratic equation
// TODO: Esto por errores de presicion puede detectar que la interseccion ocurre dentro del objeto, esto es un problema
//		 Para resolverlo hay que restarle epsilon "hacia afuera" del objeto.
float Sphere::intersect(Ray ray) {
	Vector Q = ray.origin - this->position->copy();
	float a = ray.direction.inner_product(ray.direction); // 1.f
	float b = 2 * ray.direction.inner_product(Q);
	float c = Q.inner_product(Q) - radius * radius;
	float d = b * b - 4 * a * c;

	if (d < 0) {
		// Solutions are complex, intersection does not occur
		return -1.f;
	}

	float sol = (-b - sqrtf(d)) / (2 * a); // Closest point
	if (sol >= 0) {
		return sol; // First intersection is the closest
	}

	sol = (-b + sqrtf(d)) / (2 * a); // Farest point (returned if closest is behind ray (negative position))
	if (sol >= 0) {
		return sol; // Second intersection is the closest
	}

	// All "Intersections" occurred behind the ray
	return -1.f;
}


Vector Sphere::get_normal(Vector point) {
	Vector normal = point - *(this->position);
	normal.normalize();
	return(normal);
}
