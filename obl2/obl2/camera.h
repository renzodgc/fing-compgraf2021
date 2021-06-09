#pragma once
#ifndef CAMERA_H
#define CAMERA_H

// DEPENDENCIES
// -----------------------------------------------------------------------------------

#include <iostream>
#include <utility>
#include "vector.h"

// NAMESPACE
// -----------------------------------------------------------------------------------

using namespace std;

// MAIN CLASS
// -----------------------------------------------------------------------------------

class Camera {

    private:
        Vector position;
        pair<int, int> size;

    public:
        // Constructor
        Camera(Vector position, pair<int,int> size);
        ~Camera();

        // Getters & Setters
        Vector get_position();
        pair<int, int> get_size();

    // Main methods
};

#endif
