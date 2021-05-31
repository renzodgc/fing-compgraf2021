#pragma once
#ifndef LANE_MODEL_H
#define LANE_MODEL_H

// DEPENDENCIES
// -----------------------------------------------------------------------------------

#include <iostream>
#include <vector>

#include "hud.h"
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
        Vector3 lane_position;
        vector<ScenarioObject*> objects;

        // Aux properties
        bool has_coin;
        Vector3 coin_position;

    public:
        // Constructor
        Lane(float pos_z);
        ~Lane();

        // Getters & Setters
        Vector3 get_lane_position();
        void set_lane_position(Vector3 pos);

        // Main methods
        void draw(bool use_texture);
        virtual vector<OnCollision> update(double elapsed_time, Vector3 player_position);
    };

class Wall : public Lane {

    public:
        // Constructor
        Wall(float pos_z);

        // Main methods
        vector<OnCollision> update(double elapsed_time, Vector3 player_position);

};

class Grass : public Lane {

    public:
        // Constructor
        Grass(float pos_z);
};

class Street : public Lane {

    private:
        // Basic properties
        float objects_speed;
        float spawn_rate;
        float spawn_cooldown;
        int direction;

        // Dynamic properties
        double current_cooldown;
        bool ready_to_spawn;
        
    
    public:
        // Constructor
        Street(float pos_z, unsigned int level);

        // Main methods
        vector<OnCollision> update(double elapsed_time, Vector3 player_position);
};

#endif
