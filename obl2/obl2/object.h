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
#include "ray.h"

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
        float refraction_coef; // Material type
        float transmission_coef; // 0 for opaque
        float specular_coef;
        float diffuse_coef;
        float ambience_coef;
        bool reflective;

    public:
        // Constructor
        Object(unsigned int id, Vector* position, Color diffuse_color, Color specular_color, float refraction_coef, float transmission_coef, float specular_coef, float diffuse_coef, float ambience_coef, bool reflective);
        ~Object() {};

        // Getters & Setters
        unsigned int get_id();
        ObjectIs get_type();
        Vector* get_position();
        Color get_diffuse_color();
        Color get_specular_color();
        bool is_opaque();
        float get_refraction_coef();
        float get_transmission_coef();
        float get_specular_coef();
        float get_diffuse_coef();
        float get_ambience_coef();
        bool is_reflective();

        // Main methods

        // Returns distance if the ray intersects the object, -1.f if intersection does not occur.
        virtual float intersect(Ray ray) { return 0.f; };
        virtual Vector get_normal(Vector point) { return Vector(); };

        // Aux methods
        static ObjectIs parse_object_type(string type);
};

// CHILDREN CLASSES 
// -----------------------------------------------------------------------------------

class Sphere : public Object {

    public:
        // Constructor
        Sphere(unsigned int id, Vector* position, Color diffuse_color, Color specular_color, float refraction_coef, float transmission_coef, float specular_coef, float diffuse_coef, float ambience_coef, bool reflective, float radius);

        float radius;

        // Returns distance if the ray intersects the object, -1.f if intersection does not occur.
        float intersect(Ray ray);
        Vector get_normal(Vector point);
};

#endif
