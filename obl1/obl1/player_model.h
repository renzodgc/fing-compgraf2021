#pragma once
#ifndef PLAYER_MODEL_H
#define PLAYER_MODEL_H

// DEPENDENCIES
// -----------------------------------------------------------------------------------

#include <iostream>

#include "models.h"
#include "constants.h"
#include "player_model.cpp"

// NAMESPACE
// -----------------------------------------------------------------------------------
using namespace std;

// HEADERS
// -----------------------------------------------------------------------------------
enum class PlayerIs { idle, moving_left, moving_right, moving_down, moving_up };


class Player {
private:
    position player_position, before_movement;
    float player_angle;
    PlayerIs player_state;
public:
    Player() {};
    Player(position starting_position);

    position get_player_position();
    float get_player_angle();
    void set_player_position(position new_position);
    void set_player_angle(float new_angle);
    void update(double elapsed_time);
    void move_left();
    void move_right();
    void move_up();
    void move_down();
};

#endif