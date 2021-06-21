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
// https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-plane-and-ray-disk-intersection
float Cylinder::intersect(Ray ray) {
	float t;

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
	t = sol1;
	if (sol1 > sol2) t = sol2;

	// 6. Project ray y-coordinate using calculated distance
	float r = ray.origin.y + t * ray.direction.y;

	// 7. Check if ray is in cylinder height and return distance
	if ((r >= this->position.y - (height/2) && (r <= this->position.y + (height/2)))) return t;

	// 8. Check intersection with caps of the cylinder
	t = intersect_with_base(ray, Vector(0, 1, 0), this->position + Vector(0, this->height / 2, 0)); // Top
	if (t != -1)
		return t;
	t = intersect_with_base(ray, Vector(0, -1, 0), this->position + Vector(0, -this->height / 2, 0)); // Bottom
	if (t != -1)
		return t;

	return -1.f;
}

Vector Cylinder::get_normal(Vector point, Ray ray) {
	Vector normal;
	// Check if point is at the top
	if (point.y >= this->position.y + this->height/2)
		normal = Vector(0, 1, 0);
	else if(point.y <= this->position.y - this->height/2)
		normal = Vector(0, -1, 0);
	else
		normal = Vector(point.x - this->position.x, 0, point.z - this->position.z);
	
	normal.normalize();
	return normal;
}

float Cylinder::intersect_with_base(Ray ray, Vector norm, Vector base_point) {
	// Check if normal and ray are parallel, if not, keep computing
	float denominator = norm.inner_product(ray.direction);
	if (denominator != 0) {
		float D = norm.inner_product(base_point);// +Vector(0, this->height / 2, 0));
		float distance = -(norm.inner_product(ray.origin) - D) / denominator;

		// Check if distance is positive. If not, ray is coming from behind so no return
		if (distance >= 0) {
			Vector point = ray.origin + (ray.direction * distance);
			Vector base_distance = point - base_point;
			if (base_distance.magnitude() <= this->radius)
				return distance;
		}
	}
	return -1.f;
}
