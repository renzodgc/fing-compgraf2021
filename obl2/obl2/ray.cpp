// HEADERS
// -----------------------------------------------------------------------------------

#include "ray.h"

// NAMESPACE
// -----------------------------------------------------------------------------------

using namespace std;

// METHODS
// -----------------------------------------------------------------------------------

// Constructors / Destructors
// -----------------------------------------------------------------------------------

Ray::Ray(Vector origin, Vector direction) {
	this->origin = origin;
	direction.normalize();
	this->direction = direction;
}

// Aux methods
// -----------------------------------------------------------------------------------

void Ray::print_ray() {
	cout << "Origin: " << endl;
	origin.print();
	cout << "Direction: " << endl;
	direction.print();
	cout << endl;
}
