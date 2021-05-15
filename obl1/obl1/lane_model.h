#pragma once
#ifndef LANE_MODEL_H
#define LANE_MODEL_H

// DEPENDENCIES
// -----------------------------------------------------------------------------------

#include <iostream>
#include <vector>

#include "models.h"
#include "constants.h"
#include "math_helper.h"
#include "draw_manager.h"
#include "scenario_object_model.h"


// NAMESPACE
// -----------------------------------------------------------------------------------
using namespace std;

// CLASS DEFINITION
// -----------------------------------------------------------------------------------

class Lane {

    protected:
        // References
        Draw* draw_manager;

        // Basic properties
        LaneIs lane_type;
        position lane_position;
        vector<ScenarioObject*> objects;

    public:
        // Constructor
        Lane(float pos_z);

        // Getters & Setters
        position get_lane_position();
        void set_lane_position(position pos);

        // Main methods
        void draw(bool use_texture);
    };

class Grass : public Lane {

    public:
        // Constructor
        Grass(float pos_z);
};

class Street : public Lane {

    public:
        // Constructor
        Street(float pos_z);
};

#endif
