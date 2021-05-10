#pragma once
#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <vector>
#include "models.h"

using namespace std;

// SETTINGS
const unsigned int SCR_WIDTH = 1024;
const unsigned int SCR_HEIGHT = 768;

// CAMERA
const double MOVEMENT_CAMERA_SPEED = 2.0;
const float MOUSE_SENSITIVITY = 0.1f;

// PLAYER
const double PLAYER_SPEED = 2.0;


// COLORS
const color BLACK = { 0.f, 0.f, 0.f, 1.f }; // RGBA
const color WHITE = { 1.f, 1.f, 1.f, 1.f }; // RGBA
const color RED = { 1.f, 0.f, 0.f, 1.f }; // RGBA
const color BLUE = { 0.f, 1.f, 0.f, 1.f }; // RGBA
const color GREEN = { 0.f, 0.f, 1.f, 1.f }; // RGBA
const color CYAN = { 0.f, 1.f, 1.f, 1.f }; // RGBA
const color MAGENTA = { 1.f, 0.f, 1.f, 1.f }; // RGBA
const color YELLOW = { 1.f, 1.f, 0.f, 1.f }; // RGBA
const color LIGHT_GREY = { 0.3f, 0.3f, 0.3f, 1.f }; // RGBA

// MODELS

const float TILE_LENGTH = 0.5f;

// Reference object
const vector<char> COMMANDS_REFERENCE_OBJECT = { 'C', 'V', 'V', 'V', 'V', 'C', 'V', 'V', 'V', 'V', 'C', 'V', 'V' , 'V' , 'V' };

const vector<vector<float>> DATA_REFERENCE_OBJECT = {
	{1.f, 0.f, 0.f, 1.f},
	{-TILE_LENGTH, -TILE_LENGTH, 0.f}, {TILE_LENGTH, -TILE_LENGTH, 0.f}, {TILE_LENGTH, TILE_LENGTH, 0.f}, {-TILE_LENGTH, TILE_LENGTH, 0.f},
	{0.f, 1.f, 0.f, 1.f},
	{0.f, -TILE_LENGTH, -TILE_LENGTH}, {0.f, -TILE_LENGTH, TILE_LENGTH}, {0.f, TILE_LENGTH, TILE_LENGTH}, {0.f, TILE_LENGTH, -TILE_LENGTH},
	{0.f, 0.f, 1.f, 1.f},
	{-TILE_LENGTH, 0.f, -TILE_LENGTH}, {TILE_LENGTH, 0.f, -TILE_LENGTH}, {TILE_LENGTH, 0.f, TILE_LENGTH}, {-TILE_LENGTH, 0.f, TILE_LENGTH}
};

// Cube
const vector<char> COMMANDS_CUBE_OBJECT = {
		'C', 'V', 'V', 'V', 'V',
		'C', 'V', 'V', 'V', 'V',
		'C', 'V', 'V', 'V', 'V',
		'C', 'V', 'V', 'V', 'V',
		'C', 'V', 'V', 'V', 'V',
		'C', 'V', 'V', 'V', 'V'
};

const vector<vector<float>> DATA_CUBE_OBJECT = {
	{2.55f, 2.12f, 1.73f, 1.f}, // BACK
	{-TILE_LENGTH, -TILE_LENGTH, TILE_LENGTH}, {TILE_LENGTH, -TILE_LENGTH, TILE_LENGTH}, {TILE_LENGTH, TILE_LENGTH, TILE_LENGTH}, {-TILE_LENGTH, TILE_LENGTH, TILE_LENGTH},
	{.250f, .0f, .0f, 1.f}, // FRONT
	{-TILE_LENGTH, -TILE_LENGTH, -TILE_LENGTH}, {-TILE_LENGTH, TILE_LENGTH, -TILE_LENGTH},  {TILE_LENGTH, TILE_LENGTH, -TILE_LENGTH},  {TILE_LENGTH, -TILE_LENGTH, -TILE_LENGTH},
	{2.55f, 2.12f, 1.73f, 1.f},
	{-TILE_LENGTH, TILE_LENGTH, -TILE_LENGTH}, {-TILE_LENGTH, TILE_LENGTH, TILE_LENGTH},  {TILE_LENGTH, TILE_LENGTH, TILE_LENGTH},  {TILE_LENGTH, TILE_LENGTH, -TILE_LENGTH},
	{2.55f, 2.12f, 1.73f, 1.f},
	{-TILE_LENGTH, -TILE_LENGTH, -TILE_LENGTH}, {TILE_LENGTH, -TILE_LENGTH, -TILE_LENGTH},  {TILE_LENGTH, -TILE_LENGTH, TILE_LENGTH},  {-TILE_LENGTH, -TILE_LENGTH, TILE_LENGTH},
	{2.55f, 2.12f, 1.73f, 1.f},
	{TILE_LENGTH, -TILE_LENGTH, -TILE_LENGTH}, {TILE_LENGTH, TILE_LENGTH, -TILE_LENGTH},  {TILE_LENGTH, TILE_LENGTH, TILE_LENGTH},  {TILE_LENGTH, -TILE_LENGTH, TILE_LENGTH},
	{2.55f, 2.12f, 1.73f, 1.f},
	{-TILE_LENGTH, -TILE_LENGTH, -TILE_LENGTH}, {-TILE_LENGTH, -TILE_LENGTH, TILE_LENGTH},  {-TILE_LENGTH, TILE_LENGTH, TILE_LENGTH},  {-TILE_LENGTH, TILE_LENGTH, -TILE_LENGTH}
};

// SCENARIO

// Lane
enum class LaneIs { grass, street };
const int LANE_LENGTH = 32;
const int LANE_HALF_LENGTH = LANE_LENGTH / 2;

const vector<char> COMMANDS_LANE_OBJECT = {
		'C', 'V', 'V', 'V', 'V',
};

const vector<vector<float>> DATA_LANE_INNER_OBJECT = {
	{-LANE_HALF_LENGTH, -TILE_LENGTH, -TILE_LENGTH}, {LANE_HALF_LENGTH, -TILE_LENGTH, -TILE_LENGTH},  {LANE_HALF_LENGTH, -TILE_LENGTH, TILE_LENGTH},  {-LANE_HALF_LENGTH, -TILE_LENGTH, TILE_LENGTH},
};

const vector<vector<float>> DATA_LANE_GRASS_OBJECT = {
	{0.f, 1.f, 0.f, 1.f},
	{-LANE_HALF_LENGTH, -TILE_LENGTH, -TILE_LENGTH}, {LANE_HALF_LENGTH, -TILE_LENGTH, -TILE_LENGTH},  {LANE_HALF_LENGTH, -TILE_LENGTH, TILE_LENGTH},  {-LANE_HALF_LENGTH, -TILE_LENGTH, TILE_LENGTH},
};

const vector<vector<float>> DATA_LANE_STREET_OBJECT = {
	{.2f, .2f, .2f, 1.f},
	{-LANE_HALF_LENGTH, -TILE_LENGTH, -TILE_LENGTH}, {LANE_HALF_LENGTH, -TILE_LENGTH, -TILE_LENGTH},  {LANE_HALF_LENGTH, -TILE_LENGTH, TILE_LENGTH},  {-LANE_HALF_LENGTH, -TILE_LENGTH, TILE_LENGTH},
};

// Tree
const float TREE_HEIGHT = 1.f;

const vector<char> COMMANDS_TREE_OBJECT = {
	// Tronco
		'C', 'V', 'V', 'V', 'V',
		'V', 'V', 'V', 'V',
		'V', 'V', 'V', 'V',
		'V', 'V', 'V', 'V',
		'V', 'V', 'V', 'V',
		'V', 'V', 'V', 'V',
	// Arbusto
		'C', 'V', 'V', 'V', 'V',
		'V', 'V', 'V', 'V',
		'V', 'V', 'V', 'V',
		'V', 'V', 'V', 'V',
		'V', 'V', 'V', 'V',
		'V', 'V', 'V', 'V',
};

const float TREE_TOP_HEIGHT = (TILE_LENGTH + TREE_HEIGHT);
const float TREE_STUMP_LENGHT = TILE_LENGTH - 0.25;

const vector<vector<float>> DATA_TREE_OBJECT = {
	//{.647f, .164f, .164f, 1.f} // Tronco (brown)
	{.647f, .164f, .164f, 1.f}, // BACK
	{-TREE_STUMP_LENGHT, -TREE_HEIGHT, TREE_STUMP_LENGHT}, {TREE_STUMP_LENGHT, -TREE_HEIGHT, TREE_STUMP_LENGHT}, {TREE_STUMP_LENGHT, TREE_HEIGHT, TREE_STUMP_LENGHT}, {-TREE_STUMP_LENGHT, TREE_HEIGHT, TREE_STUMP_LENGHT},
	{-TREE_STUMP_LENGHT, -TREE_HEIGHT, -TREE_STUMP_LENGHT}, {-TREE_STUMP_LENGHT, TREE_HEIGHT, -TREE_STUMP_LENGHT},  {TREE_STUMP_LENGHT, TREE_HEIGHT, -TREE_STUMP_LENGHT},  {TREE_STUMP_LENGHT, -TREE_HEIGHT, -TREE_STUMP_LENGHT},
	{-TREE_STUMP_LENGHT, TREE_HEIGHT, -TREE_STUMP_LENGHT}, {-TREE_STUMP_LENGHT, TREE_HEIGHT, TREE_STUMP_LENGHT},  {TREE_STUMP_LENGHT, TREE_HEIGHT, TREE_STUMP_LENGHT},  {TREE_STUMP_LENGHT, TREE_HEIGHT, -TREE_STUMP_LENGHT},
	{-TREE_STUMP_LENGHT, -TREE_HEIGHT, -TREE_STUMP_LENGHT}, {TREE_STUMP_LENGHT, -TREE_HEIGHT, -TREE_STUMP_LENGHT},  {TREE_STUMP_LENGHT, -TREE_HEIGHT, TREE_STUMP_LENGHT},  {-TREE_STUMP_LENGHT, -TREE_HEIGHT, TREE_STUMP_LENGHT},
	{TREE_STUMP_LENGHT, -TREE_HEIGHT, -TREE_STUMP_LENGHT}, {TREE_STUMP_LENGHT, TREE_HEIGHT, -TREE_STUMP_LENGHT},  {TREE_STUMP_LENGHT, TREE_HEIGHT, TREE_STUMP_LENGHT},  {TREE_STUMP_LENGHT, -TREE_HEIGHT, TREE_STUMP_LENGHT},
	{-TREE_STUMP_LENGHT, -TREE_HEIGHT, -TREE_STUMP_LENGHT}, {-TREE_STUMP_LENGHT, -TREE_HEIGHT, TREE_STUMP_LENGHT},  {-TREE_STUMP_LENGHT, TREE_HEIGHT, TREE_STUMP_LENGHT},  {-TREE_STUMP_LENGHT, TREE_HEIGHT, -TREE_STUMP_LENGHT},
	//{0.f, 1.f, 0.f, 1.f}, // Arbusto (gren)
	{0.f, 0.33f, 0.f, 1.f},
	{-TILE_LENGTH, TREE_HEIGHT, TILE_LENGTH}, {TILE_LENGTH, TREE_HEIGHT, TILE_LENGTH}, {TILE_LENGTH, TREE_TOP_HEIGHT, TILE_LENGTH}, {-TILE_LENGTH, TREE_TOP_HEIGHT, TILE_LENGTH},
	{-TILE_LENGTH, TREE_HEIGHT, -TILE_LENGTH}, {-TILE_LENGTH, TREE_TOP_HEIGHT, -TILE_LENGTH},  {TILE_LENGTH, TREE_TOP_HEIGHT, -TILE_LENGTH},  {TILE_LENGTH, TREE_HEIGHT, -TILE_LENGTH},
	{-TILE_LENGTH, TREE_TOP_HEIGHT, -TILE_LENGTH}, {-TILE_LENGTH, TREE_TOP_HEIGHT, TILE_LENGTH},  {TILE_LENGTH, TREE_TOP_HEIGHT, TILE_LENGTH},  {TILE_LENGTH, TREE_TOP_HEIGHT, -TILE_LENGTH},
	{-TILE_LENGTH, TREE_HEIGHT, -TILE_LENGTH}, {TILE_LENGTH, TREE_HEIGHT, -TILE_LENGTH},  {TILE_LENGTH, TREE_HEIGHT, TILE_LENGTH},  {-TILE_LENGTH, TREE_HEIGHT, TILE_LENGTH},
	{TILE_LENGTH, TREE_HEIGHT, -TILE_LENGTH}, {TILE_LENGTH, TREE_TOP_HEIGHT, -TILE_LENGTH},  {TILE_LENGTH, TREE_TOP_HEIGHT, TILE_LENGTH},  {TILE_LENGTH, TREE_HEIGHT, TILE_LENGTH},
	{-TILE_LENGTH, TREE_HEIGHT, -TILE_LENGTH}, {-TILE_LENGTH, TREE_HEIGHT, TILE_LENGTH},  {-TILE_LENGTH, TREE_TOP_HEIGHT, TILE_LENGTH},  {-TILE_LENGTH, TREE_TOP_HEIGHT, -TILE_LENGTH}
};

#endif
