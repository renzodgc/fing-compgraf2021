#pragma once
#ifndef VECTOR_3_H
#define VECTOR_3_H

// Reference: http://www.lighthouse3d.com/tutorials/view-frustum-culling/

// DEPENDENCIES
// -----------------------------------------------------------------------------------

#include <math.h>
#include <stdio.h>

// NAMESPACE
// -----------------------------------------------------------------------------------
using namespace std;

// HEADERS
// -----------------------------------------------------------------------------------


class Vector3 {

public:

	float x, y, z;

	Vector3(float x, float y, float z);
	Vector3(const Vector3& v);
	Vector3();
	~Vector3();

	Vector3 operator +(Vector3& v);
	Vector3 operator -(const Vector3& v);
	Vector3 operator *(Vector3& v);
	Vector3 operator *(float t);
	Vector3 operator /(float t);
	Vector3 operator -(void);

	float magnitude();
	void normalize();
	float inner_product(Vector3 v);
	Vector3 scalar_mult(float a);
	Vector3 cross_product(Vector3 v);
	void copy(const Vector3& v);
	void set(float x, float y, float z);

	void print();
};

#endif
