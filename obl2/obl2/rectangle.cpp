// HEADERS
// -----------------------------------------------------------------------------------

#include "rectangle.h"

// NAMESPACE
// -----------------------------------------------------------------------------------

using namespace std;

// METHODS
// -----------------------------------------------------------------------------------

// Constructors / Destructors
// -----------------------------------------------------------------------------------

Rectangle::Rectangle(
	unsigned int id, Vector position, // Main properties
	Color diffuse_color, Color specular_color, // Colors
	float refraction_coef, float transmission_coef, float specular_coef, float diffuse_coef, float ambience_coef, // Coefficients
	bool reflective, // Flags
	float length, float width, float height) // Rectangle properties

	// Parent constructor
	: Object(id, position, diffuse_color, specular_color, refraction_coef, transmission_coef, specular_coef, diffuse_coef, ambience_coef, reflective) {

	// Rectangle constructor
	this->type = ObjectIs::Rectangle;
	this->length = length;
	this->width = width;
	this->height = height;

	this->get_vertexes();
}

// Main methods
// -----------------------------------------------------------------------------------

// Reference: https://math.stackexchange.com/questions/1939423/calculate-if-vector-intersects-sphere
// Ray vector: P + tU (P base point, U unit direction)
// Sphere surface: (X - C)^2 - r^2 = 0 (C sphere center, r sphere radius, X points that intersect sphere surface)
// Quadratic equation to solve: (P + tU - C)^2 - r^2 = 0 <=> U^2 t^2 + 2t U(P-C) + (P-C)^2 - r^2 = 0
// 
// TODO: https://www.notion.so/Arreglar-errores-de-presici-n-num-rica-para-las-intersecciones-dcbe39b3f097429e9f69d1633c26f046
//		 Esto por errores de presicion puede detectar que la interseccion ocurre dentro del objeto, esto es un problema
//		 Para resolverlo hay que restarle epsilon "hacia afuera" del objeto.
float Rectangle::intersect(Ray ray) {

	// 1. Get vector between ray and rectangle (P - C)
	Vector Q = ray.origin - this->position.copy();

	// 2. Get quadratic equation parameters
	float a = ray.direction.inner_product(ray.direction); // U^2 = 1.f
	float b = 2 * ray.direction.inner_product(Q); // 2UQ
	float c = Q.inner_product(Q) - this->width * this->width; // Q^2 - r^2
	float d = b * b - 4 * a * c; // Quadratic equation b^2-4ac part

	// 3. Solutions are complex, intersection does not occur
	if (d < 0) {
		return -1.f;
	}

	// 4. Get first solution (closest one)
	float sol = (-b - sqrtf(d)) / (2 * a);
	if (sol >= 0) return sol;

	// 5. Get second solution (furthest one, returned if closest is behind ray (negative position))
	sol = (-b + sqrtf(d)) / (2 * a);
	if (sol >= 0) return sol;

	// All "Intersections" occurred behind the ray
	return -1.f;
}


Vector Rectangle::get_normal(Vector point) {
	Vector normal = point - this->position;
	normal.normalize();
	return(normal);
}

// Aux methods
// -----------------------------------------------------------------------------------

void Rectangle::get_vertexes() {

	//this->vertexes[0] = this->position;

}