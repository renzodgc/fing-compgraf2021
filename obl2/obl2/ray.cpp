// HEADERS
// -----------------------------------------------------------------------------------

#include "ray.h"

// METHODS
// -----------------------------------------------------------------------------------

// Constructors / Destructors
// -----------------------------------------------------------------------------------

Ray::Ray(Vector origin, Vector direction) {
	this->origin = origin;
	direction.normalize();
	this->direction = direction;

	// TODO: Initialize travelled_objects with value 0 and length of scenario_objects
}

// Methods
// -----------------------------------------------------------------------------------

void Ray::print_ray() {
	cout << "Origin: " << endl;
	origin.print();
	cout << "Direction: " << endl;
	direction.print();
	cout << endl;
}