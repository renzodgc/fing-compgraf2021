#pragma once
#ifndef CAMERA_HELPER_H
#define CAMERA_HELPER_H

// DEPENDENCIES
// -----------------------------------------------------------------------------------

#include <iostream>

#include "SDL.h"
#include "SDL_opengl.h"
#include <GL/glu.h>

#include "math_helper.h"

// NAMESPACE
// -----------------------------------------------------------------------------------
using namespace std;

// HEADERS
// -----------------------------------------------------------------------------------


class ThirdPersonCamera {
//private:
//
public:
    // Constructor definition
    // ThirdPersonCamera();

    // Static Methods
    
};

class OrthogonalCamera {
//private:
    //
public:
    // Constructor definition
    OrthogonalCamera();

    // Static Methods
};


class FreeCamera {
//private:
    //
public:
    // Constructor definition
    FreeCamera();

    // Static Methods
    static position update_camera_front(float mouse_offset_x, float mouse_offset_y, float& yaw, float& pitch);
    static void update_camera_eye(float camera_speed, const Uint8* keyboard_state, position camera_front, position camera_up, position& camera_eye);
};

#endif
