#pragma once
#ifndef PLAYER_MODEL_H
#define PLAYER_MODEL_H

// DEPENDENCIES
// -----------------------------------------------------------------------------------

#include <iostream>

#include "models.h"
#include "constants.h"
#include "gl_constants.h"
#include "draw_manager.h"

// NAMESPACE
// -----------------------------------------------------------------------------------
using namespace std;

// CLASS DEFINITION
// -----------------------------------------------------------------------------------

enum class PlayerIs { idle, moving_left, moving_right, moving_down, moving_up };

class Player {

    private:
        // Singleton
        Player();

        // References
        Draw* draw_manager;

        // Basic properties
        PlayerIs player_state;
        position player_position, before_movement;
        float player_angle;

    public:
        // Constructor and singleton method
        Player(Player const&) = delete;
        void operator=(Player const&) = delete;
        static Player& get_instance();

        // Getters & Setters
        position get_player_position();
        float get_player_angle();
        void set_player_position(position new_position);
        void set_player_angle(float new_angle);

        // Main methods
        void update(double elapsed_time);
        void draw(bool use_texture);

        // Motion methods
        void move_left();
        void move_right();
        void move_up();
        void move_down();
};

#endif
