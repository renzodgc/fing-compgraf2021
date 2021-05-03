#pragma once
#ifndef PLAYER_MODEL_H
#define PLAYER_MODEL_H

// DEPENDENCIES
// -----------------------------------------------------------------------------------

#include <iostream>

#include "models.h"
#include "constants.h"

// NAMESPACE
// -----------------------------------------------------------------------------------
using namespace std;

// HEADERS
// -----------------------------------------------------------------------------------


class Player {
private:
    position player_position;
    float player_angle;
public:
    Player() {};
    Player(position starting_position);

    position get_player_position();
    float get_player_angle();
    void set_player_position(position new_position);
    void set_player_angle(float new_angle);
};

#endif
