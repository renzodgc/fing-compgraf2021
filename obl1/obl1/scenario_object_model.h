#pragma once
#ifndef SCENARIO_OBJECT_MODEL_H
#define SCENARIO_OBJECT_MODEL_H

// DEPENDENCIES
// -----------------------------------------------------------------------------------

#include <iostream>

#include "hud.h"
#include "constants.h"
#include "gl_constants.h"
#include "draw_manager.h"
#include "frustum_manager.h"

// NAMESPACE
// -----------------------------------------------------------------------------------
using namespace std;

// CLASS DEFINITION
// -----------------------------------------------------------------------------------

class ScenarioObject {

    protected:
        // References
        Draw* draw_manager;

        // Basic properties
        Vector3 object_position;
        ObjectIs object_type;
        Vector3 bounding_box_radius;
        OnCollision on_collision_behaviour;

        // Helpers
        bool should_be_drawn();
    public:
        // Constructor
        ScenarioObject(Vector3 pos);

        // Getters & Setters
        Vector3 get_object_position();
        void set_object_position(Vector3 pos);
        void set_object_x(float x);
        Vector3 get_bounding_box_radius();
        void set_bounding_box_radius(Vector3 radius);
        OnCollision get_on_collision_behaviour();
        void set_on_collision_behaviour(OnCollision behaviour);
        ObjectIs get_object_type();
        void set_object_type(ObjectIs type);

        // Main methods
        virtual void draw(bool use_texture) {};
};

class Tree : public ScenarioObject {

    public:
        // Constructor
        Tree(Vector3 pos);

        // Main methods
        void draw(bool use_texture);
};

class Car : public ScenarioObject {

    private:
        // Basic properties
        int direction;

    public:
        // Constructor
        Car(Vector3 pos, int direct);

        // Main methods
        void draw(bool use_texture);
};

class Border : public ScenarioObject {

    public:
        // Constructor
        Border(Vector3 pos);

        // Main methods
        void draw(bool use_texture);
};

class Coin : public ScenarioObject {

public:
    // Constructor
    Coin(Vector3 pos);

    // Main methods
    void draw(bool use_texture);
};

#endif
