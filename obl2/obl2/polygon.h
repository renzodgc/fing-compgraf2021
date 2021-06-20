#pragma once
#ifndef POLYGON_H
#define POLYGON_H

// DEPENDENCIES
// -----------------------------------------------------------------------------------

// C++ libraries
#include <vector>
// Helpers
#include "math_helper.h"
// Structures
#include "vector.h"
// Models
#include "ray.h"

// MAIN CLASS
// -----------------------------------------------------------------------------------

class Polygon {

    public:

        // Constructor
        Polygon(Vector a, Vector b, Vector c);

        // Main properties
        Vector a, b, c;

        // Main methods
        Vector get_normal();
        Vector get_normal(Ray ray);
};

#endif
