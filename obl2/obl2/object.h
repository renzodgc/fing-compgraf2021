#pragma once
#ifndef OBJECT_H
#define OBJECT_H

// DEPENDENCIES
// -----------------------------------------------------------------------------------

#include <math.h>
#include <stdio.h>
#include <string>

#include "vector.h"
#include "colors.h"

// ENUMERATES
// -----------------------------------------------------------------------------------

enum class ObjectIs { TriangleMesh, Sphere, Cillinder, Rectangle };

// MAIN CLASS
// -----------------------------------------------------------------------------------

class Object {

    protected:
        ObjectIs type;
        unsigned int id;
        Vector* position;
        Color color;
        float transparency;
        float refraction_coef;
        bool reflective;

    public:
        // Constructor
        Object(unsigned int id, Vector* position, Color color, float transparency, float refraction_coef, bool reflective);
        ~Object();

        // Getters & Setters
        ObjectIs get_type();
        unsigned int get_id();
        Vector* get_position();
        Color get_color();
        float get_transparency();
        float get_refraction_coef();
        bool get_reflective();

        // Main methods

        // Aux methods
        static ObjectIs parse_object_type(string type);
};

// CHILDREN CLASSES 
// -----------------------------------------------------------------------------------

class Sphere : public Object {

    public:
        // Constructor
        Sphere(unsigned int id, Vector* position, Color color, float transparency, float refraction_coef, bool reflective);


};

#endif
