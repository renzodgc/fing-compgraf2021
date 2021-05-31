// Reference: http://www.lighthouse3d.com/tutorials/view-frustum-culling/

#include "vector3.h"

// Constructor/Destructors
// -----------------------------------------------------------------------------------


Vector3::Vector3(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3::Vector3(const Vector3& v) {
	x = v.x;
	y = v.y;
	z = v.z;
}


Vector3::Vector3() {
	x = 0;
	y = 0;
	z = 0;
}


Vector3::~Vector3() {}

// Methods
// -----------------------------------------------------------------------------------

Vector3 Vector3::operator+(Vector3& v) {
	Vector3 res;

	res.x = x + v.x;
	res.y = y + v.y;
	res.z = z + v.z;

	return(res);
}

Vector3 Vector3::operator-(const Vector3& v) {
	Vector3 res;

	res.x = x - v.x;
	res.y = y - v.y;
	res.z = z - v.z;

	return(res);
}

Vector3 Vector3::operator-(void) {
	Vector3 res;

	res.x = -x;
	res.y = -y;
	res.z = -z;

	return(res);
}

// cross product
Vector3 Vector3::operator*(Vector3& v) {
	Vector3 res;

	res.x = y * v.z - z * v.y;
	res.y = z * v.x - x * v.z;
	res.z = x * v.y - y * v.x;

	return (res);
}

Vector3 Vector3::operator*(float t) {
	Vector3 res;

	res.x = x * t;
	res.y = y * t;
	res.z = z * t;

	return (res);
}


Vector3 Vector3::operator/(float t) {
	Vector3 res;

	res.x = x / t;
	res.y = y / t;
	res.z = z / t;

	return (res);
}



float Vector3::magnitude() {
	return((float)sqrt(x * x + y * y + z * z));
}

void Vector3::normalize() {
	float len;

	len = magnitude();
	if (len) {
		x /= len;;
		y /= len;
		z /= len;
	}
}


float Vector3::inner_product(Vector3 v) {
	return (x * v.x + y * v.y + z * v.z);
}

Vector3 Vector3::scalar_mult(float a) {
	Vector3 res;

	res.x = x * a;
	res.y = y * a;
	res.z = z * a;

	return res;
}

Vector3 Vector3::cross_product(Vector3 v) {
	Vector3 res;

	res.x = y * v.z - z * v.y;
	res.y = -(x * v.z - z * v.x);
	res.z = x * v.y - y * v.x;

	return res;
}

void Vector3::copy(const Vector3& v) {
	x = v.x;
	y = v.y;
	z = v.z;
}

void Vector3::set(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

// For debug pruposes: Prints a vector
// -----------------------------------------------------------------------------------


void Vector3::print() {
	printf("Vector3(%f, %f, %f) ", x, y, z);
}
