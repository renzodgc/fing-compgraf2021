#pragma once
#ifndef CAMERA_HELPER_H
#define CAMERA_HELPER_H

// DEPENDENCIES
// -----------------------------------------------------------------------------------

#include <iostream>

#include "SDL.h"
#include "SDL_opengl.h"
#include <GL/glu.h>

#include "constants.h"
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
    ThirdPersonCamera();

    // Static Methods
    static void start_third_person_view(position player_position, camera& new_camera);
};

class IsometricCamera {
//private:
    //
public:
    // Constructor definition
    IsometricCamera();

    // Static Methods
    static void start_isometric_view(position player_position, camera& new_camera);
    static void orthogonal_projection();
    static void leave_isometric_view(position player_position);
};


class FreeViewCamera {
//private:
    //
public:
    // Constructor definition
    FreeViewCamera();

    // Static Methods
    static void start_free_view(position player_position, camera& new_camera);
    static void update_camera_front(float mouse_offset_x, float mouse_offset_y, camera& current_camera);
    static void update_camera_eye(float camera_speed, const Uint8* keyboard_state, camera& current_camera);
};

#endif
