#pragma once
#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <vector>
#include "gl_constants.h"
#include "models.h"

using namespace std;

// SETTINGS
// ---------------------------------------------------------------------------------------

const unsigned int SCR_WIDTH = 1024;
const unsigned int SCR_HEIGHT = 768;

// CAMERA
// ---------------------------------------------------------------------------------------

const double MOVEMENT_CAMERA_SPEED = 2.0;
const float MOUSE_SENSITIVITY = 0.1f;

// PLAYER
// ---------------------------------------------------------------------------------------

const double PLAYER_SPEED = 7.0;

// GAME
// ---------------------------------------------------------------------------------------

const unsigned int LEVEL_RAISE_COEF = 10;

// LANE
// ---------------------------------------------------------------------------------------

const unsigned int LANE_TYPES = 3;

const int LANES_INTERVAL = 10;
const int INITIAL_LANES_INTERVAL = 10;

const unsigned int MAX_GRASS_COEF = 4;
const unsigned int MAX_STREET_COEF = 2;

// FILE ROUTES
// ---------------------------------------------------------------------------------------

const string ROUTE_PLAYER_TEXTURE = "resources/Chicken02Col.jpg";
const string ROUTE_PLAYER_OBJECT = "resources/Chicken02.obj";

const string ROUTE_CAR_TEXTURE = "resources/Truck04Colour.png";
const string ROUTE_CAR_OBJECT = "resources/Truck02.obj";

#endif
