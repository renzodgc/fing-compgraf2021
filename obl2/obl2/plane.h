#ifndef PLANE_H
#define PLANE_H

// DEPENDENCIES
// -----------------------------------------------------------------------------------

#include <stdio.h>
#include "vector.h"

// MAIN CLASS
// -----------------------------------------------------------------------------------

class Plane {

public:
	Vector normal, point;
	float d;

	Plane::Plane(Vector& v1, Vector& v2, Vector& v3);
	Plane::Plane(void);
	Plane::~Plane();

	void set3Points(Vector& v1, Vector& v2, Vector& v3);
	void set_normal_and_point(Vector& normal, Vector& point);
	void set_coefficients(float a, float b, float c, float d);
	float distance(Vector& p);

	void print();
};

#endif
