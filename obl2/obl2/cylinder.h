#pragma once
#ifndef CYLINDER_H
#define CYLINDER_H

// DEPENDENCIES
// -----------------------------------------------------------------------------------

#include "object.h"

// MAIN CLASS
// -----------------------------------------------------------------------------------

class Cylinder : public Object {

public:
    // Constructor
    Cylinder(unsigned int id, Vector position, // Main properties
        Color diffuse_color, Color specular_color, // Colors
        float refraction_coef, float transmission_coef, float specular_coef, float diffuse_coef, float ambience_coef, // Coefficients
        bool reflective, // Flags
        float radius, float height); // Cylinder properties

    // Main properties
    float radius;
    float height;

    // Main methods
    float intersect(Ray ray); // Returns distance if the ray intersects the object, -1.f if intersection does not occur.
    Vector get_normal(Vector point, Ray ray);
};

#endif
#pragma once
