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

private:

    // Main properties
    Vector a, b, c;

public:

    // Constructor
    Polygon(Vector a, Vector b, Vector c);

    // Main methods
    Vector get_normal();
};

#endif
