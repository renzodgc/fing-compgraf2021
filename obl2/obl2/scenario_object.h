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
    ObjectIs type;
    Vector centre_position;
    Color color;
    float transparency;
    float refraction_coef;
    bool reflective;

public:
    // Constructor
    ScenarioObject(Vector centre_position, Color color, float transparency, float refraction_coef, bool reflective);
    ~ScenarioObject();

    // Getters & Setters
    ObjectIs get_type();
    Vector get_centre_position();
    Color get_color();
    float get_transparency();
    float get_refraction_coef();
    bool get_reflective();

    // Main methods
};

#endif
