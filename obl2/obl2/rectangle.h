#pragma once
#ifndef RECTANGLE_H
#define RECTANGLE_H

// DEPENDENCIES
// -----------------------------------------------------------------------------------

#include "object.h"

// MAIN CLASS
// -----------------------------------------------------------------------------------

class Rectangle : public Object {

    private:

        // Aux properties
        static const int faces = 6;
        Vector centers[faces]; // right, left, top, bottom, back, front
        Vector normals[faces]; // right, left, top, bottom, back, front

        // Aux methods
        void get_centers();
        void get_normals();

    public:

        // Constructor
        Rectangle(unsigned int id, Vector position, // Main properties
            Color diffuse_color, Color specular_color, // Colors
            float refraction_coef, float transmission_coef, float specular_coef, float diffuse_coef, float ambience_coef, // Coefficients
            bool reflective, // Flags
            float length, float width, float height); // Rectangle properties

        // Main properties
        float length;
        float width;
        float height;

        // Main methods
        float intersect(Ray ray); // Returns distance if the ray intersects the object, -1.f if intersection does not occur.
        Vector get_normal(Vector point);
};

#endif
