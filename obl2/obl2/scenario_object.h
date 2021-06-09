#pragma once
#ifndef SCENARIO_OBJECT_H
#define SCENARIO_OBJECT_H

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

class ScenarioObject {

protected:
    short id;
    ObjectIs type;
    Vector centre_position;
    Color diffuse_color;
    Color specular_color;
    float transparency; // If true object is not opaque
    float refraction_coef;
    bool reflective;

public:
    // Constructor
    ScenarioObject(short id, Vector centre_position, Color diffuse_color, Color specular_color, float transparency, float refraction_coef, bool reflective);
    ~ScenarioObject();

    // Getters & Setters
    short get_id();
    ObjectIs get_type();
    Vector get_centre_position();
    Color get_diffuse_color();
    Color get_specular_color();
    float get_transparency();
    float get_refraction_coef();
    bool get_reflective();

    // Main methods
};

#endif
