#pragma once
#ifndef CAMERA_H
#define CAMERA_H

// DEPENDENCIES
// -----------------------------------------------------------------------------------

// C++ Libraries
#include <iostream>
#include <utility>
// Structures
#include "vector.h"

// NAMESPACE
// -----------------------------------------------------------------------------------

using namespace std;

// MAIN CLASS
// -----------------------------------------------------------------------------------

class Camera {

    private:
        Vector position;
        Vector window_position;

    public:
        // Constructor
        Camera(Vector position, Vector window_position);
        ~Camera();

        // Getters & Setters
        Vector get_position();
        void set_position(Vector position);
        Vector get_window_position();
        void set_window_position(Vector window_position);
};

#endif
