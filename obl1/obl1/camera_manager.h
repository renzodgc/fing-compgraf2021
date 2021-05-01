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
#include "player_manager.h"

// NAMESPACE
// -----------------------------------------------------------------------------------
using namespace std;

// HEADERS
// -----------------------------------------------------------------------------------


class Camera {
private:
    Player * player;

    CameraType selected_camera;
    position camera_eye;   // Specifies the position of the eye point.
    position camera_front; // Specifies the position of the reference point.
    position camera_up;    // Specifies the direction of the up vector.
    float yaw;
    float pitch;

    position camera_position;
    float third_person_distance_from_player, third_person_angle_around_player;
    float third_person_horizontal_distance_from_player, third_person_vertical_distance_from_player;
    float third_person_angle, third_person_offset_x, third_person_offset_z;

    void isometric_camera_update_position();

    void third_person_camera_update_position();
    void third_person_camera_update_angle(float mouse_offset_x, float mouse_offset_y);

    void free_view_camera_update_position(double elapsed_time, const Uint8* keyboard_state);
    void free_view_camera_update_angle(float mouse_offset_x, float mouse_offset_y);

public:
    Camera(){};
    Camera(Player * player_model);

    void start_third_person_view();
    void start_isometric_view();
    void start_free_view();
    void update_position(double elapsed_time, const Uint8* keyboard_state);
    void update_angle(float mouse_offset_x, float mouse_offset_y);
    void call_look_at();
};

#endif
