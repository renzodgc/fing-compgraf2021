#ifndef RAY_H
#define RAY_H

#include <iostream>       // std::cout
#include <stack>          // std::stack
#include <vector>         // std::vector

#include "vector.h"
#include "refraction_coefficients.h"

using namespace std;

class Ray {
public:

	Vector origin;
	Vector direction;
	vector<short> travelled_objects; // Its lenght is equal to the number of objects on scene. 0 = not travelled, 1 = entered, 2 = exited
	stack<short> refraction_stack; // Keep state of current medium IDs. 
		// If a medium is exited but it's not current medium then ignore refraction.
		// it's value equals the object's ID.

	Ray();
	Ray(Vector origin, Vector direction);
	~Ray();
};

#endif
