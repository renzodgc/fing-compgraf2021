#pragma once
#ifndef LIGHT_H
#define LIGHT_H

// DEPENDENCIES
// -----------------------------------------------------------------------------------

// C++ Libraries
#include <iostream>
#include <utility>
// Constants
#include "colors.h"
// Structures
#include "vector.h"

// NAMESPACE
// -----------------------------------------------------------------------------------

using namespace std;

// MAIN CLASS
// -----------------------------------------------------------------------------------

class Light {

    private:
        Vector* position;
        Color color;

    public:
        // Constructor
        Light(Vector* position, Color color);
        ~Light();

        // Getters & Setters
        Vector* get_position();
        Color get_color();
};

#endif
