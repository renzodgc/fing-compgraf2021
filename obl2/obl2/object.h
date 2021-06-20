#pragma once
#ifndef OBJECT2_H
#define OBJECT2_H

// DEPENDENCIES
// -----------------------------------------------------------------------------------

// C++ libraries
#include <math.h>
#include <stdio.h>
#include <string>
#include <vector>
// Constants
#include "colors.h"
// Structures
#include "vector.h"
// Models
#include "ray.h"

// ENUMERATES
// -----------------------------------------------------------------------------------

enum class ObjectIs { TriangleMesh, Sphere, Cylinder };

// MAIN CLASS
// -----------------------------------------------------------------------------------

class Object {

    protected:

        // Main properties
        unsigned int id;
        ObjectIs type;
        Vector position;

        // Colors
        Color diffuse_color;
        Color specular_color;

        // Coefficients
        float refraction_coef; // Range [1,..)
        float transmission_coef; // Range [0,1] (opaque, transparent)
        float specular_coef;
        float diffuse_coef;
        float ambience_coef;

        // Flags
        bool reflective; // false nonreflective, true reflective 

    public:

        // Constructor
        Object(unsigned int id, Vector position, Color diffuse_color, Color specular_color, float refraction_coef, float transmission_coef, float specular_coef, float diffuse_coef, float ambience_coef, bool reflective);
        ~Object() {};

        // Getters & Setters - Main properties
        unsigned int get_id();
        ObjectIs get_type();
        Vector get_position();
        // Getters & Setters - Colors
        Color get_diffuse_color();
        Color get_specular_color();
        // Getters & Setters - Coefficients
        float get_refraction_coef();
        float get_transmission_coef();
        float get_specular_coef();
        float get_diffuse_coef();
        float get_ambience_coef();
        // Getters & Setters - Flags
        bool is_opaque();
        bool is_reflective();

        // Main abstract methods
        virtual float intersect(Ray ray) { return -1.f; }; // Returns distance if the ray intersects the object, -1.f if intersection does not occur.
        virtual Vector get_normal(Vector point) { return Vector(); };

        // Aux static methods
        static ObjectIs parse_object_type(std::string type);
};

#endif
