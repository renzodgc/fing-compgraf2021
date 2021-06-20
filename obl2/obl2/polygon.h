#pragma once
#ifndef POLYGON_H
#define POLYGON_H

// DEPENDENCIES
// -----------------------------------------------------------------------------------

// C++ libraries
#include <vector>
// Structures
#include "vector.h"

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
        Vector get_normal(Vector direction);
};

#endif
