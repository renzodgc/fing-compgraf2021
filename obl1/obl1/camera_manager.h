#pragma once
#ifndef CAMERA_MANAGER_H
#define CAMERA_MANAGER_H

// DEPENDENCIES
// -----------------------------------------------------------------------------------

#include <iostream>

#include "SDL.h"
#include "SDL_opengl.h"
#include <GL/glu.h>

#include "models.h"
#include "constants.h"
#include "math_helper.h"

// NAMESPACE
// -----------------------------------------------------------------------------------
using namespace std;

// HEADERS
// -----------------------------------------------------------------------------------


class Camera {
private:
    CameraType selected_camera;
    position camera_eye;   // Specifies the position of the eye point.
    position camera_front; // Specifies the position of the reference point.
    position camera_up;    // Specifies the direction of the up vector.
    float yaw;
    float pitch;

    void isometric_camera_update_position(position player_position);

    void third_person_camera_update_position(position player_position);
    void third_person_camera_update_angle(float mouse_offset_x, float mouse_offset_y);

    void free_view_camera_update_position(double elapsed_time, const Uint8* keyboard_state);
    void free_view_camera_update_angle(float mouse_offset_x, float mouse_offset_y);

public:
    void start_third_person_view(position player_position);
    void start_isometric_view(position player_position);
    void start_free_view(position player_position);
    void update_position(position player_position, double elapsed_time, const Uint8* keyboard_state);
    void update_angle(float mouse_offset_x, float mouse_offset_y);
    void call_look_at();
};

#endif
