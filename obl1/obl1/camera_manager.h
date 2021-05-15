#pragma once
#ifndef CAMERA_MANAGER_H
#define CAMERA_MANAGER_H

// DEPENDENCIES
// -----------------------------------------------------------------------------------

#include <iostream>
#include <math.h>

#include "SDL.h"
#include "SDL_opengl.h"
#include <GL/glu.h>

#include "models.h"
#include "constants.h"
#include "gl_constants.h"
#include "math_helper.h"
#include "player_model.h"

// NAMESPACE
// -----------------------------------------------------------------------------------
using namespace std;

// CLASS DEFINITION
// -----------------------------------------------------------------------------------

class Camera {

    private:
        // Singleton
        Camera();

        // References
        Player * player;

        // Basic camera properties
        CameraType selected_camera;
        position camera_eye;   // Specifies the position of the eye point.
        position camera_front; // Specifies the position of the reference point.
        position camera_up;    // Specifies the direction of the up vector.
        float yaw;
        float pitch;
        float distance_from_player;

        // Third person camera properties
        position camera_position;
        float third_person_angle_around_player;
        float third_person_horizontal_distance_from_player, third_person_vertical_distance_from_player;
        float third_person_offset_x, third_person_offset_z;

        // Isometric camera internal update methods
        void isometric_camera_update_position();

        // Third person camera internal update methods
        void third_person_camera_update_position();
        void third_person_camera_update_angle(float mouse_offset_x, float mouse_offset_y);
        void third_person_camera_update_distance(double elapsed_time, Sint32 mouse_wheel_y);

        // Free view camera internal update methods
        void free_view_camera_update_position(double elapsed_time, const Uint8* keyboard_state);
        void free_view_camera_update_angle(float mouse_offset_x, float mouse_offset_y);

    public:
        // Constructor and singleton method
        Camera(Camera const&) = delete;
        void operator=(Camera const&) = delete;
        static Camera& get_instance();

        // Camera type methods
        void start_third_person_view();
        void start_isometric_view();
        void start_free_view();

        // External update methods
        void update_position(double elapsed_time, const Uint8* keyboard_state);
        void update_angle(float mouse_offset_x, float mouse_offset_y);
        void update_distance(double elapsed_time, Sint32 mouse_wheel_y);
        
        // Other methods
        void call_look_at();
};

#endif
