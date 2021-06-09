// HEADERS
// -----------------------------------------------------------------------------------

#include "ray.h"

// METHODS
// -----------------------------------------------------------------------------------

// Constructors / Destructors
// -----------------------------------------------------------------------------------

Ray::Ray() {}

Ray::Ray(Vector origin, Vector direction) {
	this->origin = origin;
	this->direction = direction;
	// TODO: Initialize travelled_objects with value 0 and length of scenario_objects
}

Ray::~Ray() {}

// Methods
// -----------------------------------------------------------------------------------
