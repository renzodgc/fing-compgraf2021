#pragma once
#ifndef LANE_MODEL_H
#define LANE_MODEL_H

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


class Lane {
private:
    position lane_position;
public:
    Lane() {};
    Lane(position pos);

    position get_lane_position();
    void set_lane_position(position pos);
};

#endif
