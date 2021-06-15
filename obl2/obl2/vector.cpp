// HEADERS
// -----------------------------------------------------------------------------------

#include "vector.h"

// METHODS
// -----------------------------------------------------------------------------------

// Constructors / Destructors
// -----------------------------------------------------------------------------------

Vector::Vector(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}
Vector::Vector(const Vector& v) {
	x = v.x;
	y = v.y;
	z = v.z;
}
Vector::Vector() {
	x = 0;
	y = 0;
	z = 0;
}
Vector::~Vector() {}

// Methods
// -----------------------------------------------------------------------------------

Vector Vector::operator+(Vector& v) {
	Vector res;

	res.x = x + v.x;
	res.y = y + v.y;
	res.z = z + v.z;

	return(res);
}

Vector Vector::operator-(const Vector& v) {
	Vector res;

	res.x = x - v.x;
	res.y = y - v.y;
	res.z = z - v.z;

	return(res);
}

Vector Vector::operator-(void) {
	Vector res;

	res.x = -x;
	res.y = -y;
	res.z = -z;

	return(res);
}

// Cross Product
Vector Vector::operator*(Vector& v) {
	Vector res;

	res.x = y * v.z - z * v.y;
	res.y = z * v.x - x * v.z;
	res.z = x * v.y - y * v.x;

	return (res);
}

// Scalar product
Vector Vector::operator*(float t) {
	Vector res;

	res.x = x * t;
	res.y = y * t;
	res.z = z * t;

	return (res);
}

Vector Vector::operator/(float t) {
	Vector res;

	res.x = x / t;
	res.y = y / t;
	res.z = z / t;

	return (res);
}

float Vector::magnitude() {
	return((float)sqrt(x * x + y * y + z * z));
}

void Vector::normalize() {
	float len;

	len = magnitude();
	if (len) {
		x /= len;;
		y /= len;
		z /= len;
	}
}

float Vector::euclid_distance(Vector v) {
	return Vector(x - v.x, y - v.y, z - v.z).magnitude();
}

float Vector::inner_product(Vector v) {
	return (x * v.x + y * v.y + z * v.z);
}

Vector Vector::scalar_mult(float a) {
	Vector res;

	res.x = x * a;
	res.y = y * a;
	res.z = z * a;

	return res;
}

Vector Vector::cross_product(Vector v) {
	Vector res;

	res.x = y * v.z - z * v.y;
	res.y = -(x * v.z - z * v.x);
	res.z = x * v.y - y * v.x;

	return res;
}

Vector Vector::copy() {
	Vector res;

	res.x = x;
	res.y = y;
	res.z = z;

	return res;
}

void Vector::set(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

// For debug pruposes: Prints a vector
// -----------------------------------------------------------------------------------

void Vector::print() {
	printf("Vector(%f, %f, %f) \n", x, y, z);
}
