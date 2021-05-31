// HEADERS
// -----------------------------------------------------------------------------------

#include "plane.h"

// METHODS
// -----------------------------------------------------------------------------------

// Constructors / Destructors
// -----------------------------------------------------------------------------------

Plane::Plane(Vector& v1, Vector& v2, Vector& v3) {
	set3Points(v1, v2, v3);
}
Plane::Plane() {}
Plane::~Plane() {}

// Methods
// -----------------------------------------------------------------------------------

void Plane::set3Points(Vector& v1, Vector& v2, Vector& v3) {
	Vector aux1, aux2;

	aux1 = v1 - v2;
	aux2 = v3 - v2;

	normal = aux2 * aux1;

	normal.normalize();
	point.copy(v2);
	d = -(normal.inner_product(point));
}

void Plane::set_normal_and_point(Vector& normal, Vector& point) {
	this->normal.copy(normal);
	this->normal.normalize();
	d = -(this->normal.inner_product(point));
}

void Plane::set_coefficients(float a, float b, float c, float d) {
	// set the normal vector
	normal.set(a, b, c);
	//compute the lenght of the vector
	float l = normal.magnitude();
	// normalize the vector
	normal.set(a / l, b / l, c / l);
	// and divide d by th length as well
	this->d = d / l;
}

float Plane::distance(Vector& p) {
	return (d + normal.inner_product(p));
}

// For debug pruposes: Prints a plane
// -----------------------------------------------------------------------------------

void Plane::print() {
	printf("Plane("); normal.print(); printf("# %f)", d);
}
