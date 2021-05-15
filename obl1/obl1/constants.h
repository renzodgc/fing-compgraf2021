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

// LANE
// ---------------------------------------------------------------------------------------

enum class LaneIs { grass, street };

// FILE ROUTES
// ---------------------------------------------------------------------------------------

const string ROUTE_PLAYER_TEXTURE = "resources/Chicken02Col.jpg";
const string ROUTE_PLAYER_OBJECT = "resources/Chicken02.obj";

#endif
