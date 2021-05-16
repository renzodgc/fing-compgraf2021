#pragma once
#ifndef LANE_MODEL_H
#define LANE_MODEL_H

// DEPENDENCIES
// -----------------------------------------------------------------------------------

#include <iostream>
#include <vector>

#include "models.h"
#include "constants.h"
#include "gl_constants.h"
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
        ~Lane();

        // Getters & Setters
        position get_lane_position();
        void set_lane_position(position pos);

        // Main methods
        void draw(bool use_texture);
        virtual void update(double elapsed_time);
    };

class Wall : public Lane {

    public:
        // Constructor
        Wall(float pos_z);

};

class Grass : public Lane {

    public:
        // Constructor
        Grass(float pos_z);
};

class Street : public Lane {

    private:
        // General properties
        float objects_speed;
        int direction;
        double current_cooldown;

        // Spawn properties
        bool ready_to_spawn;
        float spawn_rate;
        float spawn_cooldown;
    
    public:
        // Constructor
        Street(float pos_z);
        void update(double elapsed_time);
};

// Reference: https://stackoverflow.com/questions/991335/how-to-erase-delete-pointers-to-objects-stored-in-a-vector
// Function object to delete lanes
struct scenario_object_deleter {
    void operator()(ScenarioObject*& e) { // important to take pointer by reference!
        delete e;
        e = NULL;
    }
};

#endif
