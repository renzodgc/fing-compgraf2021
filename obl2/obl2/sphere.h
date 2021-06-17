#pragma once
#ifndef SPHERE_H
#define SPHERE_H

// DEPENDENCIES
// -----------------------------------------------------------------------------------

#include "object.h"

// MAIN CLASS
// -----------------------------------------------------------------------------------

class Sphere : public Object {

    public:
        // Constructor
        Sphere(unsigned int id, Vector* position, Color diffuse_color, Color specular_color, float refraction_coef, float transmission_coef, float specular_coef, float diffuse_coef, float ambience_coef, bool reflective, float radius);

        // Main properties
        float radius;

        // Main methods
        float intersect(Ray ray); // Returns distance if the ray intersects the object, -1.f if intersection does not occur.
        Vector get_normal(Vector point);
};

#endif
