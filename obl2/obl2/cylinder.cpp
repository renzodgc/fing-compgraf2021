// HEADERS
// -----------------------------------------------------------------------------------

#include "cylinder.h"

// NAMESPACE
// -----------------------------------------------------------------------------------

using namespace std;

// METHODS
// -----------------------------------------------------------------------------------

// Constructors / Destructors
// -----------------------------------------------------------------------------------

Cylinder::Cylinder(
	unsigned int id, Vector position, // Main properties
	Color diffuse_color, Color specular_color, // Colors
	float refraction_coef, float transmission_coef, float specular_coef, float diffuse_coef, float ambience_coef, // Coefficients
	bool reflective, // Flags
	float radius, float height) // Cylinder properties
	
	// Parent constructor
	: Object(id, position, diffuse_color, specular_color, refraction_coef, transmission_coef, specular_coef, diffuse_coef, ambience_coef, reflective) {
		
	// Cylinder constructor
	this->type = ObjectIs::Cylinder;
	this->radius = radius;
	this->height = height;
}

// Main methods
// -----------------------------------------------------------------------------------

// Reference: https://github.com/iceman201/RayTracing
float Cylinder::intersect(Ray ray) {;

	// 1. Get quadratic equation parameters
	float a = (ray.direction.x * ray.direction.x) + (ray.direction.z * ray.direction.z);
	float b = 2 * (ray.direction.x * (ray.origin.x - this->position.x) + ray.direction.z * (ray.origin.z - this->position.z));
	float c = (ray.origin.x - this->position.x) * (ray.origin.x - this->position.x) + (ray.origin.z - this->position.z) * (ray.origin.z - this->position.z) - (this->radius * this->radius);
	float d = b * b - 4 * (a * c);

	// 2. Solutions are complex, intersection does not occur
	if (d < 0) return -1.f;

	// 3. Get first solution (closest one)
	float sol1 = (-b - sqrtf(d)) / (2 * a);

	// 4. Get second solution (furthest one, returned if closest is behind ray (negative position))
	float sol2 = (-b + sqrtf(d)) / (2 * a);

	// 5. Get smaller one
	float t = sol1;
	if (sol1 > sol2) t = sol2;

	// 6. Project ray y-coordinate using calculated distance
	float r = ray.origin.y + t * ray.direction.y;

	// 7. Check if ray is in cylinder height and return distance
	if ((r >= this->position.y - (height/2) && (r <= this->position.y + (height/2)))) return t;

	return -1.f;
}

Vector Cylinder::get_normal(Vector point, Ray ray) {
	Vector normal = Vector(point.x - this->position.x, 0, point.z - this->position.z);
	normal.normalize();
	return normal;
}
