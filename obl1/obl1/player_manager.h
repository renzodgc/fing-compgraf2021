#pragma once
#ifndef PLAYER_MANAGER_H
#define PLAYER_MANAGER_H

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
public:
    Player() {};
    Player(position starting_position);

    position get_player_position();
    void set_player_position(position new_position);
};

#endif
