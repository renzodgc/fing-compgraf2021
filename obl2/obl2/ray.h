#ifndef RAY_H
#define RAY_H

// DEPENDENCIES
// -----------------------------------------------------------------------------------

// C++ Libraries
#include <iostream>       // std::cout
#include <stack>          // std::stack
#include <vector>         // std::vector
// Constants
#include "refraction_coefficients.h"
// Structures
#include "vector.h"

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
		std::stack<int> refraction_stack; // Keep state of current medium IDs. 
			// TODO: If a medium is exited but it's not current medium then ignore refraction.
			// it's value equals the object's ID.
	
		// Aux methods
		void print_ray();
};

#endif
