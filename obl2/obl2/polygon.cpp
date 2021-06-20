// HEADERS
// -----------------------------------------------------------------------------------

#include "polygon.h"

// NAMESPACE
// -----------------------------------------------------------------------------------

using namespace std;

// POLYGON METHODS
// -----------------------------------------------------------------------------------

// Constructors / Destructors
// -----------------------------------------------------------------------------------

Polygon::Polygon(Vector a, Vector b, Vector c) {
	this->a = a;
	this->b = b;
	this->c = c;
}

// Main methods
// -----------------------------------------------------------------------------------

Vector Polygon::get_normal() {

	// Get polygon's sides as vectors
	Vector length = this->b - this->a;
	Vector width = this->c - this->a;

	// Get normal by cross product them and normalize it
	Vector normal = length.cross_product(width);
	normal.normalize();
	return normal;
}

// Reference: https://math.stackexchange.com/questions/214187/point-on-the-left-or-right-side-of-a-plane-in-3d-space
Vector Polygon::get_normal(Ray ray) {

	// Get polygon's sides as vectors
	Vector length = this->b - this->a;
	Vector width = this->c - this->a;
	Vector distance = ray.origin - this->a;

	// Get normal by cross product them and normalize it
	Vector normal = width.cross_product(length);
	normal.normalize();
	if (determinant3x3(-length, -width, -distance) <= 0) {
		normal = -normal;
	}
	return normal;
}