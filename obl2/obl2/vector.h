#pragma once
#ifndef VECTOR_H
#define VECTOR_H

// DEPENDENCIES
// -----------------------------------------------------------------------------------

// C++ Libraries
#include <math.h>
#include <stdio.h>

// MAIN CLASS
// -----------------------------------------------------------------------------------

class Vector {

	public:

		// Constructor
		Vector(float x, float y, float z);
		Vector(const Vector& v);
		Vector();
		~Vector();

		// Main properties
		float x, y, z;

		// Operators
		Vector operator +(Vector& v);
		Vector operator -(const Vector& v);
		Vector operator *(Vector& v);
		Vector operator *(float t);
		Vector operator /(float t);
		Vector operator -(void);

		// Getters & Setters
		void set(float x, float y, float z);

		// Main methods
		float magnitude();
		void normalize();
		float euclid_distance(Vector v);
		float inner_product(Vector v);
		Vector scalar_mult(float a);
		Vector cross_product(Vector v);
		Vector copy();

		// Aux methods
		void print();
};

#endif
