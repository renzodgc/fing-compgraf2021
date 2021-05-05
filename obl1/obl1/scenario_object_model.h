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
private:
    position object_position;
    ObjectIs object_type;
public:
    ScenarioObject() {};
    ScenarioObject(position pos);

    position get_object_position();
    void set_object_position(position pos);
    virtual void draw();
};

class Tree : public ScenarioObject {
public:
    Tree() = delete;

    void draw();
};

class Car : public ScenarioObject {
public:
    Car() = delete;

    void draw();
};

class Border : public ScenarioObject {
public:
    Border() = delete;

    void draw();
};

#endif
