#pragma once
#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>
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

enum class CameraType { isometric, third_person, free_view };
const double MOVEMENT_CAMERA_SPEED = 6.0;
const float MOUSE_SENSITIVITY = 0.1f;

const float NEAR_PLANE_CAMERA = 0.1f;
const float FAR_PLANE_CAMERA = 75.0f;
const float ANGLE_CAMERA = 45.f;
const float RATIO_CAMERA = SCR_WIDTH / (float)SCR_HEIGHT;

// DRAW MANAGER
// ---------------------------------------------------------------------------------------

enum class ObjType { squares, triangles };
const bool FRUSTUM_CULLING = false; // TODO: Fix

// PLAYER
// ---------------------------------------------------------------------------------------

enum class PlayerIs { idle, moving_left, moving_right, moving_down, moving_up };
const double PLAYER_SPEED = 6.0;
const float PLAYER_MAX_HEIGHT = 0.5f;

// MATH
// ---------------------------------------------------------------------------------------

const double PI = 3.14159265358979323846;
const double ANG2RAD = PI / 180.0;

// GAME
// ---------------------------------------------------------------------------------------

enum class OnCollision { bounce, death, coin };
const unsigned int LEVEL_RAISE_COEF = 10;
const bool IMMORTAL = false;
const bool LOG_FPS = false;

// LIGHTNING
// ---------------------------------------------------------------------------------------

enum class LightningType { day, sunset, night };
const int LIGHTNING_TYPES = 3;

// LANE
// ---------------------------------------------------------------------------------------

enum class LaneIs { wall, grass, street };
const unsigned int LANE_TYPES = 3;

const int LANES_INTERVAL = 10; // Amount of lanes created/destroyed when going forward
const int INITIAL_LANES_INTERVAL = 10; // Amount of lanes created from origin when starting game

const unsigned int MAX_GRASS_COEF = 4; // Max amount of grass lanes together
const unsigned int MAX_STREET_COEF = 2; // Max amount of street lanes together (multiplied by level)

const unsigned int COIN_SPAWN_RATE = 20; // 100/COIN_SPAWN_RATE gives the probability of coin spawning

// STREET
// ---------------------------------------------------------------------------------------

const float BASE_SPAWN_COOLDOWN_COEF = 3.0f;

const unsigned int BASE_SPAWN_RATE_COEF = 10;
const unsigned int SPAWN_RATE_RANDOM_COEF = 15;

const unsigned int BASE_SPEED_COEF = 2;
const unsigned int SPEED_COEF = 4;
const unsigned int SPEED_RANDOM_COEF = 2;
const float SPEED_SCALING_COEF = 0.5f;

// OBJECTS
// ---------------------------------------------------------------------------------------

enum class ObjectIs { car, tree, border, coin };

// FILE ROUTES
// ---------------------------------------------------------------------------------------

const string ROUTE_PLAYER_TEXTURE = "resources/Chicken02Col.jpg";
const string ROUTE_PLAYER_OBJECT = "resources/Chicken02.obj";

const string ROUTE_GRASS_TEXTURE = "resources/Grass.gif";
const string ROUTE_STREET_TEXTURE = "resources/Street.png";

const string ROUTE_CAR_TEXTURE = "resources/Truck04Colour.png";
const string ROUTE_CAR_OBJECT = "resources/Truck02.obj";

const string ROUTE_WOOD_TEXTURE = "resources/Wood.jpg";
const string ROUTE_LEAVES_TEXTURE = "resources/leaves.jpg";
const string ROUTE_COIN_TEXTURE = "resources/coin.jpg";
const string ROUTE_WALL_TEXTURE = "resources/wall.jpg";

const string ROUTE_KEYBINDS_TEXTURE = "resources/keybinds.jpg";

#endif

