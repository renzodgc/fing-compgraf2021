#ifndef PLANE_H
#define PLANE_H

// Reference: http://www.lighthouse3d.com/tutorials/view-frustum-culling/

#include <stdio.h>
#include "vector3.h"

class Plane {

public:
	Vector3 normal, point;
	float d;

	Plane::Plane(Vector3& v1, Vector3& v2, Vector3& v3);
	Plane::Plane(void);
	Plane::~Plane();

	void set3Points(Vector3& v1, Vector3& v2, Vector3& v3);
	void set_normal_and_point(Vector3& normal, Vector3& point);
	void set_coefficients(float a, float b, float c, float d);
	float distance(Vector3& p);

	void print();
};

#endif
