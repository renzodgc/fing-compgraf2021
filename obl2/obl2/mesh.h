#pragma once
#ifndef MESH_H
#define MESH_H

// DEPENDENCIES
// -----------------------------------------------------------------------------------

#include "polygon.h"
#include "object.h"

// MAIN CLASS
// -----------------------------------------------------------------------------------

class Mesh : public Object {

public:

    // Constructor
    Mesh(unsigned int id, Vector position, // Main properties
        Color diffuse_color, Color specular_color, // Colors
        float refraction_coef, float transmission_coef, float specular_coef, float diffuse_coef, float ambience_coef, // Coefficients
        bool reflective, // Flags
        std::vector<Polygon*> polygons); // Mesh properties

    // Main properties
    std::vector<Polygon*> polygons;

    // Main methods
    float intersect(Ray ray); // Returns distance if the ray intersects the object, -1.f if intersection does not occur.
    Vector get_normal(Vector point, Ray ray);
};

#endif
