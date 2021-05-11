#pragma once
#ifndef LANE_MODEL_H
#define LANE_MODEL_H

// DEPENDENCIES
// -----------------------------------------------------------------------------------

#include <iostream>
#include <vector>

#include "models.h"
#include "constants.h"
#include "draw_manager.h"
#include "scenario_object_model.h"

#include "draw_manager.h"

// NAMESPACE
// -----------------------------------------------------------------------------------
using namespace std;

// HEADERS
// -----------------------------------------------------------------------------------


class Lane {
protected:
    position lane_position;
    LaneIs lane_type;
    vector<ScenarioObject*> objects;
public:
    Lane(float pos_z);

    position get_lane_position();
    void set_lane_position(position pos);
    void draw();
};

class Grass : public Lane {
public:
    Grass(float pos_z);

    void draw();
};

class Street : public Lane {
public:
    Street(float pos_z);

    void draw();
};

#endif
