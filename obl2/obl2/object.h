#pragma once
#ifndef OBJECT_H
#define OBJECT_H

// DEPENDENCIES
// -----------------------------------------------------------------------------------

#include <math.h>
#include <stdio.h>

#include "vector.h"
#include "colors.h"

// NAMESPACE
// -----------------------------------------------------------------------------------

using namespace std;

// ENUMERATES
// -----------------------------------------------------------------------------------

enum class ObjectIs { TriangleMesh, Sphere, Cillinder, Rectangle };

// MAIN CLASS
// -----------------------------------------------------------------------------------

class Object {

    protected:
        ObjectIs type;
        Vector* position;
        Color* color;
        float transparency;
        float refraction_coef;
        bool reflective;

    public:
        // Constructor
        Object(Vector* position, Color* color, float transparency, float refraction_coef, bool reflective);
        ~Object();

        // Getters & Setters
        ObjectIs get_type();
        Vector* get_position();
        Color* get_color();
        float get_transparency();
        float get_refraction_coef();
        bool get_reflective();

        // Main methods
};

#endif
