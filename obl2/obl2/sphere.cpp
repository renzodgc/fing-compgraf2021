// HEADERS
// -----------------------------------------------------------------------------------

#include "sphere.h"

// NAMESPACE
// -----------------------------------------------------------------------------------

using namespace std;

// METHODS
// -----------------------------------------------------------------------------------

// Constructors / Destructors
// -----------------------------------------------------------------------------------

Sphere::Sphere(
	unsigned int id, Vector* position, // Main properties
	Color diffuse_color, Color specular_color, // Colors
	float refraction_coef, float transmission_coef, float specular_coef, float diffuse_coef, float ambience_coef, // Coefficients
	bool reflective, // Flags
	float radius) // Sphere properties

	// Parent constructor
	: Object(id, position, diffuse_color, specular_color, refraction_coef, transmission_coef, specular_coef, diffuse_coef, ambience_coef, reflective) {

	// Sphere constructor
	this->type = ObjectIs::Sphere;
	this->radius = radius;
}

// Main methods
// -----------------------------------------------------------------------------------

// Reference: https://math.stackexchange.com/questions/1939423/calculate-if-vector-intersects-sphere
// Solve quadratic equation
// TODO: https://www.notion.so/Arreglar-errores-de-presici-n-num-rica-para-las-intersecciones-dcbe39b3f097429e9f69d1633c26f046
//		 Esto por errores de presicion puede detectar que la interseccion ocurre dentro del objeto, esto es un problema
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
