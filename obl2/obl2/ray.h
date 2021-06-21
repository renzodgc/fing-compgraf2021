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
		std::stack<int> refraction_stack; // Keep state of current mediums (entered) IDs. 
	
		// Aux methods
		void print_ray();
};

#endif
