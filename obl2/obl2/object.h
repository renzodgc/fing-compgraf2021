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
        unsigned int id;
        ObjectIs type;
        Vector* position;
        Color diffuse_color;
        Color specular_color;
        float transparency;
        float refraction_coef;
        bool reflective;

    public:
        // Constructor
        Object(unsigned int id, Vector* position, Color diffuse_color, Color specular_color, float transparency, float refraction_coef, bool reflective);
        ~Object();

        // Getters & Setters
        unsigned int get_id();
        ObjectIs get_type();
        Vector* get_position();
        Color get_diffuse_color();
        Color get_specular_color();
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
        Sphere(unsigned int id, Vector* position, Color diffuse_color, Color specular_color, float transparency, float refraction_coef, bool reflective);


};

#endif
