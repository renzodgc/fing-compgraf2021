#pragma once
#ifndef SCENARIO_OBJECT_MODEL_H
#define SCENARIO_OBJECT_MODEL_H

// DEPENDENCIES
// -----------------------------------------------------------------------------------

#include <iostream>

#include "models.h"
#include "constants.h"
#include "draw_manager.h"

// NAMESPACE
// -----------------------------------------------------------------------------------
using namespace std;

// HEADERS
// -----------------------------------------------------------------------------------

const enum ObjectIs { car, tree, border };

class ScenarioObject {
protected:
    position object_position;
    ObjectIs object_type;
    Draw* draw_manager;
public:
    ScenarioObject(position pos);

    position get_object_position();
    void set_object_position(position pos);
    ObjectIs get_object_type();
    void set_object_type(ObjectIs type);
    virtual void draw(bool use_texture) {};
};

class Tree : public ScenarioObject {
public:
    Tree(position pos);

    void draw(bool use_texture);
};

class Car : public ScenarioObject {
private:
    float velocity;
    position initial_position;
public:
    Car(position pos, float vel);

    void draw(bool use_texture);
};

class Border : public ScenarioObject {
public:
    Border(position pos);

    void draw(bool use_texture);
};

#endif
