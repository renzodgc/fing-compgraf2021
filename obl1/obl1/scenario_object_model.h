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
#include "frustum_manager.h"

// NAMESPACE
// -----------------------------------------------------------------------------------
using namespace std;

// HEADERS
// -----------------------------------------------------------------------------------

const enum ObjectIs { car, tree, border };

class ScenarioObject {
protected:
    Draw* draw_manager;
    Vector3 object_position;
    ObjectIs object_type;
    Vector3 bounding_box_radius;
    OnCollision on_collision_behaviour;

    bool should_be_drawn();
public:
    ScenarioObject(Vector3 pos);

    Vector3 get_object_position();
    void set_object_position(Vector3 pos);
    void set_object_x(float x);
    Vector3 get_bounding_box_radius();
    void set_bounding_box_radius(Vector3 radius);
    OnCollision get_on_collision_behaviour();
    void set_on_collision_behaviour(OnCollision behaviour);
    ObjectIs get_object_type();
    void set_object_type(ObjectIs type);
    virtual void draw(bool use_texture) {};
};

class Tree : public ScenarioObject {
public:
    Tree(Vector3 pos);

    void draw(bool use_texture);
};

class Car : public ScenarioObject {
private:
    int direction;
public:
    Car(Vector3 pos, int direct);

    void draw(bool use_texture);
};

class Border : public ScenarioObject {
public:
    Border(Vector3 pos);

    void draw(bool use_texture);
};

#endif
