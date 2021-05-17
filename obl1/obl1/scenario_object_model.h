#pragma once
#ifndef SCENARIO_OBJECT_MODEL_H
#define SCENARIO_OBJECT_MODEL_H

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

class ScenarioObject {

    protected:
        // References
        Draw* draw_manager;

        // Basic properties
        position object_position;
        ObjectIs object_type;
        vector3d bounding_box_radius;
        OnCollision on_collision_behaviour;

    public:
        // Constructor
        ScenarioObject(position pos);

        // Getters & Setters
        position get_object_position();
        void set_object_position(position pos);
        void set_object_x(float x);
        vector3d get_bounding_box_radius();
        void set_bounding_box_radius(vector3d radius);
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
        Tree(position pos);

        // Main methods
        void draw(bool use_texture);
};

class Car : public ScenarioObject {

    private:
        // Basic properties
        int direction;

    public:
        // Constructor
        Car(position pos, int direct);

        // Main methods
        void draw(bool use_texture);
};

class Border : public ScenarioObject {

    public:
        // Constructor
        Border(position pos);

        // Main methods
        void draw(bool use_texture);
};

#endif
