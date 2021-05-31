#pragma once
#ifndef VECTOR_H
#define VECTOR_H

// DEPENDENCIES
// -----------------------------------------------------------------------------------

#include <math.h>
#include <stdio.h>

// NAMESPACE
// -----------------------------------------------------------------------------------

using namespace std;

// MAIN CLASS
// -----------------------------------------------------------------------------------

class Vector {

public:

	float x, y, z;

	Vector(float x, float y, float z);
	Vector(const Vector& v);
	Vector();
	~Vector();

	Vector operator +(Vector& v);
	Vector operator -(const Vector& v);
	Vector operator *(Vector& v);
	Vector operator *(float t);
	Vector operator /(float t);
	Vector operator -(void);

	float magnitude();
	void normalize();
	float inner_product(Vector v);
	Vector scalar_mult(float a);
	Vector cross_product(Vector v);
	void copy(const Vector& v);
	void set(float x, float y, float z);

	void print();
};

#endif
