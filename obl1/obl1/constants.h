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

// Reference object
const vector<char> COMMANDS_REFERENCE_OBJECT = { 'C', 'V', 'V', 'V', 'V', 'C', 'V', 'V', 'V', 'V', 'C', 'V', 'V' , 'V' , 'V' };

const vector<vector<float>> DATA_REFERENCE_OBJECT = {
	{1.f, 0.f, 0.f, 1.f},
	{-0.5f, -0.5f, 0.f}, {0.5f, -0.5f, 0.f}, {0.5f, 0.5f, 0.f}, {-0.5f, 0.5f, 0.f},
	{0.f, 1.f, 0.f, 1.f},
	{0.f, -0.5f, -0.5f}, {0.f, -0.5f, 0.5f}, {0.f, 0.5f, 0.5f}, {0.f, 0.5f, -0.5f},
	{0.f, 0.f, 1.f, 1.f},
	{-0.5f, 0.f, -0.5f}, {0.5f, 0.f, -0.5f}, {0.5f, 0.f, 0.5f}, {-0.5f, 0.f, 0.5f}
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
	{-0.5f, -0.5f, 0.5f}, {0.5f, -0.5f, 0.5f}, {0.5f, 0.5f, 0.5f}, {-0.5f, 0.5f, 0.5f},
	{.250f, .0f, .0f, 1.f}, // FRONT
	{-0.5f, -0.5f, -0.5f}, {-0.5f, 0.5f, -0.5f},  {0.5f, 0.5f, -0.5f},  {0.5f, -0.5f, -0.5f},
	{2.55f, 2.12f, 1.73f, 1.f},
	{-0.5f, 0.5f, -0.5f}, {-0.5f, 0.5f, 0.5f},  {0.5f, 0.5f, 0.5f},  {0.5f, 0.5f, -0.5f},
	{2.55f, 2.12f, 1.73f, 1.f},
	{-0.5f, -0.5f, -0.5f}, {0.5f, -0.5f, -0.5f},  {0.5f, -0.5f, 0.5f},  {-0.5f, -0.5f, 0.5f},
	{2.55f, 2.12f, 1.73f, 1.f},
	{0.5f, -0.5f, -0.5f}, {0.5f, 0.5f, -0.5f},  {0.5f, 0.5f, 0.5f},  {0.5f, -0.5f, 0.5f},
	{2.55f, 2.12f, 1.73f, 1.f},
	{-0.5f, -0.5f, -0.5f}, {-0.5f, -0.5f, 0.5f},  {-0.5f, 0.5f, 0.5f},  {-0.5f, 0.5f, -0.5f}
};

// Lane
const vector<char> COMMANDS_LANE_OBJECT = {
		'C', 'V', 'V', 'V', 'V',
};

enum class LaneIs { grass, street };
const float LANE_LENGTH = 11.f;

const vector<vector<float>> DATA_LANE_INNER_OBJECT = {
	{-LANE_LENGTH, -0.5f, -0.5f}, {LANE_LENGTH, -0.5f, -0.5f},  {LANE_LENGTH, -0.5f, 0.5f},  {-LANE_LENGTH, -0.5f, 0.5f},
};

const vector<vector<float>> DATA_LANE_GRASS_OBJECT = {
	{0.f, 1.f, 0.f, 1.f},
	{-LANE_LENGTH, -0.5f, -0.5f}, {LANE_LENGTH, -0.5f, -0.5f},  {LANE_LENGTH, -0.5f, 0.5f},  {-LANE_LENGTH, -0.5f, 0.5f},
};

const vector<vector<float>> DATA_LANE_STREET_OBJECT = {
	{.2f, .2f, .2f, 1.f},
	{-LANE_LENGTH, -0.5f, -0.5f}, {LANE_LENGTH, -0.5f, -0.5f},  {LANE_LENGTH, -0.5f, 0.5f},  {-LANE_LENGTH, -0.5f, 0.5f},
};

#endif
