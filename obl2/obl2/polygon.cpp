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
	Vector length = this->a - this->b;
	Vector width = this->a - this->c;

	// Get normal by cross product them and normalize it
	Vector normal = length.cross_product(width);
	normal.normalize();
	return normal;
}