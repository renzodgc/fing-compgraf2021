#include "Plane.h"

Plane::Plane(Vector3& v1, Vector3& v2, Vector3& v3) {
	set3Points(v1, v2, v3);
}

Plane::Plane() {}

Plane::~Plane() {}


void Plane::set3Points(Vector3& v1, Vector3& v2, Vector3& v3) {
	Vector3 aux1, aux2;

	aux1 = v1 - v2;
	aux2 = v3 - v2;

	normal = aux2 * aux1;

	normal.normalize();
	point.copy(v2);
	d = -(normal.inner_product(point));
}

void Plane::set_normal_and_point(Vector3& normal, Vector3& point) {
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


float Plane::distance(Vector3& p) {
	return (d + normal.inner_product(p));
}

void Plane::print() {
	printf("Plane("); normal.print(); printf("# %f)", d);
}
