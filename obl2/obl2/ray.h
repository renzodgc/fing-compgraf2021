#ifndef RAY_H
#define RAY_H

// DEPENDENCIES
// -----------------------------------------------------------------------------------

#include <iostream>       // std::cout
#include <stack>          // std::stack
#include <vector>         // std::vector

#include "vector.h"
#include "refraction_coefficients.h"

// MAIN CLASS
// -----------------------------------------------------------------------------------

class Ray {

	public:

		// Constructor
		Ray() {};
		Ray(Vector origin, Vector direction);
		~Ray() {};

		// Main properties
		Vector origin;
		Vector direction;
		std::vector<short> travelled_objects; // Its length is equal to the number of objects on scene. 0 = not travelled, 1 = entered, 2 = exited
		std::stack<short> refraction_stack; // Keep state of current medium IDs. 
			// If a medium is exited but it's not current medium then ignore refraction.
			// it's value equals the object's ID.
	
		// Aux methods
		void print_ray();
};

#endif
