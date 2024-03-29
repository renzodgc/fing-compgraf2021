#pragma once
#ifndef GL_CONSTANTS_H
#define GL_CONSTANTS_H

#include <vector>
#include "constants.h"
#include "hud.h"

using namespace std;

// VALUES
// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Tiles
const float TILE_LENGTH = 0.5f;

// Lane
const int LANE_LENGTH = 24;
const int LANE_HALF_LENGTH = LANE_LENGTH / 2;

// Tree
const float TREE_HEIGHT = 1.f;
const float TREE_TOP_HEIGHT = (TILE_LENGTH + TREE_HEIGHT);
const float TREE_STUMP_LENGTH = TILE_LENGTH - 0.25;

// COLORS
// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
const color BLACK = { 0.f, 0.f, 0.f, 1.f }; // RGBA
const color WHITE = { 1.f, 1.f, 1.f, 1.f }; // RGBA
const color RED = { 1.f, 0.f, 0.f, 1.f }; // RGBA
const color BLUE = { 0.f, 1.f, 0.f, 1.f }; // RGBA
const color GREEN = { 0.f, 0.f, 1.f, 1.f }; // RGBA
const color CYAN = { 0.f, 1.f, 1.f, 1.f }; // RGBA
const color MAGENTA = { 1.f, 0.f, 1.f, 1.f }; // RGBA
const color YELLOW = { 1.f, 1.f, 0.f, 1.f }; // RGBA
const color LIGHT_GREY = { 0.3f, 0.3f, 0.3f, 1.f }; // RGBA

// OBJECTS
// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Cube
const vector<char> COMMANDS_CUBE_OBJECT = {
		'C',
		'N', 'T', 'V', 'T', 'V', 'T', 'V', 'T', 'V',
		'N', 'T', 'V', 'T', 'V', 'T', 'V', 'T', 'V',
		'N', 'T', 'V', 'T', 'V', 'T', 'V', 'T', 'V',
		'N', 'T', 'V', 'T', 'V', 'T', 'V', 'T', 'V',
		'N', 'T', 'V', 'T', 'V', 'T', 'V', 'T', 'V',
		'N', 'T', 'V', 'T', 'V', 'T', 'V', 'T', 'V'
};
const vector<vector<float>> DATA_CUBE_OBJECT = {
	{0.2f, 0.2f, 0.2f, 1.f}, // BACK
	{ 0.f, 0.f, 1.f }, // Down
	{0.f, 0.f}, {-TILE_LENGTH, -TILE_LENGTH, TILE_LENGTH},
	{1.f, 0.f}, {TILE_LENGTH, -TILE_LENGTH, TILE_LENGTH},
	{1.f, 1.f}, {TILE_LENGTH, TILE_LENGTH, TILE_LENGTH},
	{0.f, 1.f}, {-TILE_LENGTH, TILE_LENGTH, TILE_LENGTH},
	{ 0.f, 0.f, -1.f }, // Up
	{0.f, 0.f}, {-TILE_LENGTH, -TILE_LENGTH, -TILE_LENGTH},
	{1.f, 0.f}, {TILE_LENGTH, -TILE_LENGTH, -TILE_LENGTH},
	{1.f, 1.f}, {TILE_LENGTH, TILE_LENGTH, -TILE_LENGTH},
	{0.f, 1.f}, {-TILE_LENGTH, TILE_LENGTH, -TILE_LENGTH},
	{ 0.f, 1.f, 0.f }, // Top
	{0.f, 0.f}, {-TILE_LENGTH, TILE_LENGTH, -TILE_LENGTH},
	{1.f, 0.f}, {TILE_LENGTH, TILE_LENGTH, -TILE_LENGTH},
	{1.f, 1.f}, {TILE_LENGTH, TILE_LENGTH, TILE_LENGTH},
	{0.f, 1.f}, {-TILE_LENGTH, TILE_LENGTH, TILE_LENGTH},
	{ 0.f, -1.f, 0.f }, // Bottom
	{0.f, 0.f}, {-TILE_LENGTH, -TILE_LENGTH, -TILE_LENGTH},
	{1.f, 0.f}, {TILE_LENGTH, -TILE_LENGTH, -TILE_LENGTH},
	{1.f, 1.f}, {TILE_LENGTH, -TILE_LENGTH, TILE_LENGTH},
	{0.f, 1.f}, {-TILE_LENGTH, -TILE_LENGTH, TILE_LENGTH},
	{ 1.f, 0.f, 0.f }, // Right
	{0.f, 0.f}, {TILE_LENGTH, -TILE_LENGTH, -TILE_LENGTH},
	{1.f, 0.f}, {TILE_LENGTH, TILE_LENGTH, -TILE_LENGTH},
	{1.f, 1.f}, {TILE_LENGTH, TILE_LENGTH, TILE_LENGTH},
	{0.f, 1.f}, {TILE_LENGTH, -TILE_LENGTH, TILE_LENGTH},
	{ -1.f, 0.f, 0.f }, // Left
	{0.f, 0.f}, {-TILE_LENGTH, -TILE_LENGTH, -TILE_LENGTH},
	{1.f, 0.f}, {-TILE_LENGTH, TILE_LENGTH, -TILE_LENGTH},
	{1.f, 1.f}, {-TILE_LENGTH, TILE_LENGTH, TILE_LENGTH},
	{0.f, 1.f}, {-TILE_LENGTH, -TILE_LENGTH, TILE_LENGTH}
};

// Lane objects
const vector<char> COMMANDS_LANE_OBJECT = {
		'C', 'N', 'V', 'V', 'V', 'V',
};
const vector<char> COMMANDS_GRASS_OBJECT = {
		'C', 'N', 'T', 'V', 'T', 'V', 'T', 'V', 'T', 'V'
};
const vector<char> COMMANDS_STREET_OBJECT = {
		'C', 'N', 'T', 'V', 'T', 'V', 'T', 'V', 'T', 'V'
};
const vector<char> COMMANDS_LANE_WALL_OBJECT = {
		'C', 'N', 'T', 'V', 'T', 'V', 'T', 'V', 'T', 'V',
			 'N', 'T', 'V', 'T', 'V', 'T', 'V', 'T', 'V',
			 'N', 'T', 'V', 'T', 'V', 'T', 'V', 'T', 'V',
			 'N', 'T', 'V', 'T', 'V', 'T', 'V', 'T', 'V'
};
const vector<vector<float>> DATA_LANE_INNER_OBJECT = {
	{-LANE_HALF_LENGTH, -TILE_LENGTH, -TILE_LENGTH}, {LANE_HALF_LENGTH, -TILE_LENGTH, -TILE_LENGTH},  {LANE_HALF_LENGTH, -TILE_LENGTH, TILE_LENGTH},  {-LANE_HALF_LENGTH, -TILE_LENGTH, TILE_LENGTH},
};
const vector<vector<float>> DATA_LANE_GRASS_OBJECT = {
	{0.f, 0.7f, 0.f, 1.f},
	{0.f, 1.f, 0.f}, // Top
	{0.f, 0.f}, {-LANE_HALF_LENGTH, -TILE_LENGTH, -TILE_LENGTH},
	{LANE_LENGTH, 0.f}, {LANE_HALF_LENGTH, -TILE_LENGTH, -TILE_LENGTH},
	{LANE_LENGTH, 1.f}, {LANE_HALF_LENGTH, -TILE_LENGTH, TILE_LENGTH},
	{0.f, 1.f}, {-LANE_HALF_LENGTH, -TILE_LENGTH, TILE_LENGTH},
};
const vector<vector<float>> DATA_LANE_STREET_OBJECT = {
	{.2f, .2f, .2f, 1.f},
	{0.f, 1.f, 0.f}, // Top
	{0.f, 0.f}, {-LANE_HALF_LENGTH, -TILE_LENGTH, -TILE_LENGTH},
	{LANE_LENGTH, 0.f}, {LANE_HALF_LENGTH, -TILE_LENGTH, -TILE_LENGTH},
	{LANE_LENGTH, 1.f}, {LANE_HALF_LENGTH, -TILE_LENGTH, TILE_LENGTH},
	{0.f, 1.f}, {-LANE_HALF_LENGTH, -TILE_LENGTH, TILE_LENGTH},
};
const vector<vector<float>> DATA_LANE_WALL_OBJECT = {
	{0.2f, 0.2f, 0.2f, 1.f},
	{0.f, -1.f, 0.f}, // Bottom
	{0.f, 0.f}, {-LANE_HALF_LENGTH, -TILE_LENGTH, -TILE_LENGTH},
	{1.f, 0.f}, {LANE_HALF_LENGTH, -TILE_LENGTH, -TILE_LENGTH},
	{1.f, 1.f}, {LANE_HALF_LENGTH, -TILE_LENGTH, TILE_LENGTH},
	{0.f, 1.f}, {-LANE_HALF_LENGTH, -TILE_LENGTH, TILE_LENGTH},
	{0.f, 0.f, -1.f}, // Up
	{0.f, 0.f}, {-LANE_HALF_LENGTH, -TILE_LENGTH, -TILE_LENGTH},
	{1.f, 0.f}, {LANE_HALF_LENGTH, -TILE_LENGTH, -TILE_LENGTH},
	{1.f, 1.f}, {LANE_HALF_LENGTH, TILE_LENGTH * 3, -TILE_LENGTH},
	{0.f, 1.f}, {-LANE_HALF_LENGTH, TILE_LENGTH * 3, -TILE_LENGTH},
	{0.f, 1.f, 0.f}, // Top
	{0.f, 0.f}, {-LANE_HALF_LENGTH, TILE_LENGTH * 3, -TILE_LENGTH},
	{1.f, 0.f}, {LANE_HALF_LENGTH, TILE_LENGTH * 3, -TILE_LENGTH},
	{1.f, 1.f}, {LANE_HALF_LENGTH, TILE_LENGTH * 3, TILE_LENGTH},
	{0.f, 1.f}, {-LANE_HALF_LENGTH, TILE_LENGTH * 3, TILE_LENGTH},
	{0.f, 0.f, 1.f}, // Down
	{0.f, 0.f}, {-LANE_HALF_LENGTH, -TILE_LENGTH, TILE_LENGTH},
	{1.f, 0.f}, {LANE_HALF_LENGTH, -TILE_LENGTH, TILE_LENGTH},
	{1.f, 1.f}, {LANE_HALF_LENGTH, TILE_LENGTH * 3, TILE_LENGTH},
	{0.f, 1.f}, {-LANE_HALF_LENGTH, TILE_LENGTH * 3, TILE_LENGTH},
};

// Tree Stump
const vector<char> COMMANDS_TREE_STUMP_OBJECT = {
	'C',
	'N', 'T', 'V', 'T', 'V', 'T', 'V', 'T', 'V',
	'N', 'T', 'V', 'T', 'V', 'T', 'V', 'T', 'V',
	'N', 'T', 'V', 'T', 'V', 'T', 'V', 'T', 'V',
	'N', 'T', 'V', 'T', 'V', 'T', 'V', 'T', 'V',
	'N', 'T', 'V', 'T', 'V', 'T', 'V', 'T', 'V',
	'N', 'T', 'V', 'T', 'V', 'T', 'V', 'T', 'V'
};
const vector<vector<float>> DATA_TREE_STUMP_OBJECT = {
	{.647f, .164f, .164f, 1.f}, // Stump (Brown)
	{ 0.f, 0.f, 1.f }, // Down
	{0.f, 0.f}, {-TREE_STUMP_LENGTH, -TREE_HEIGHT, TREE_STUMP_LENGTH},
	{1.f, 0.f}, {TREE_STUMP_LENGTH, -TREE_HEIGHT, TREE_STUMP_LENGTH},
	{1.f, TREE_HEIGHT}, {TREE_STUMP_LENGTH, TREE_HEIGHT, TREE_STUMP_LENGTH},
	{0.f, TREE_HEIGHT}, {-TREE_STUMP_LENGTH, TREE_HEIGHT, TREE_STUMP_LENGTH},
	{ 0.f, 0.f, -1.f }, // Up
	{0.f, 0.f}, {-TREE_STUMP_LENGTH, -TREE_HEIGHT, -TREE_STUMP_LENGTH},
	{1.f, 0.f}, {TREE_STUMP_LENGTH, -TREE_HEIGHT, -TREE_STUMP_LENGTH},
	{1.f, TREE_HEIGHT}, {TREE_STUMP_LENGTH, TREE_HEIGHT, -TREE_STUMP_LENGTH},
	{0.f, TREE_HEIGHT}, {-TREE_STUMP_LENGTH, TREE_HEIGHT, -TREE_STUMP_LENGTH},
	{ 0.f, 1.f, 0.f }, // Top
	{0.f, 0.f}, {-TREE_STUMP_LENGTH, TREE_HEIGHT, -TREE_STUMP_LENGTH},
	{1.f, 0.f}, {TREE_STUMP_LENGTH, TREE_HEIGHT, -TREE_STUMP_LENGTH},
	{1.f, TREE_HEIGHT}, {TREE_STUMP_LENGTH, TREE_HEIGHT, TREE_STUMP_LENGTH},
	{0.f, TREE_HEIGHT}, {-TREE_STUMP_LENGTH, TREE_HEIGHT, TREE_STUMP_LENGTH},
	{ 0.f, -1.f, 0.f }, // Bottom
	{0.f, 0.f}, {-TREE_STUMP_LENGTH, -TREE_HEIGHT, -TREE_STUMP_LENGTH},
	{1.f, 0.f}, {TREE_STUMP_LENGTH, -TREE_HEIGHT, -TREE_STUMP_LENGTH},
	{1.f, TREE_HEIGHT}, {TREE_STUMP_LENGTH, -TREE_HEIGHT, TREE_STUMP_LENGTH},
	{0.f, TREE_HEIGHT}, {-TREE_STUMP_LENGTH, -TREE_HEIGHT, TREE_STUMP_LENGTH},
	{ 1.f, 0.f, 0.f }, // Right
	{0.f, 0.f}, {TREE_STUMP_LENGTH, -TREE_HEIGHT, -TREE_STUMP_LENGTH},
	{1.f, 0.f}, {TREE_STUMP_LENGTH, TREE_HEIGHT, -TREE_STUMP_LENGTH},
	{1.f, TREE_HEIGHT}, {TREE_STUMP_LENGTH, TREE_HEIGHT, TREE_STUMP_LENGTH},
	{0.f, TREE_HEIGHT}, {TREE_STUMP_LENGTH, -TREE_HEIGHT, TREE_STUMP_LENGTH},
	{ -1.f, 0.f, 0.f }, // Left
	{0.f, 0.f}, {-TREE_STUMP_LENGTH, -TREE_HEIGHT, -TREE_STUMP_LENGTH},
	{1.f, 0.f}, {-TREE_STUMP_LENGTH, TREE_HEIGHT, -TREE_STUMP_LENGTH},
	{1.f, TREE_HEIGHT}, {-TREE_STUMP_LENGTH, TREE_HEIGHT, TREE_STUMP_LENGTH},
	{0.f, TREE_HEIGHT}, {-TREE_STUMP_LENGTH, -TREE_HEIGHT, TREE_STUMP_LENGTH},
};

// Tree leaves
const vector<char> COMMANDS_TREE_LEAVES_OBJECT = {
	'C',
	'N', 'T', 'V', 'T', 'V', 'T', 'V', 'T', 'V',
	'N', 'T', 'V', 'T', 'V', 'T', 'V', 'T', 'V',
	'N', 'T', 'V', 'T', 'V', 'T', 'V', 'T', 'V',
	'N', 'T', 'V', 'T', 'V', 'T', 'V', 'T', 'V',
	'N', 'T', 'V', 'T', 'V', 'T', 'V', 'T', 'V',
	'N', 'T', 'V', 'T', 'V', 'T', 'V', 'T', 'V'
};
const vector<vector<float>> DATA_TREE_LEAVES_OBJECT = {
	{ 0.f, 0.33f, 0.f, 1.f }, // Leaves (Dark Green)
	{ 0.f, 0.f, 1.f }, // Down
	{0.f, 0.f}, { -TILE_LENGTH, TREE_HEIGHT, TILE_LENGTH },
	{1.f, 0.f}, { TILE_LENGTH, TREE_HEIGHT, TILE_LENGTH },
	{1.f, 1.f}, { TILE_LENGTH, TREE_TOP_HEIGHT, TILE_LENGTH },
	{0.f, 1.f}, { -TILE_LENGTH, TREE_TOP_HEIGHT, TILE_LENGTH },
	{ 0.f, 0.f, -1.f }, // Up
	{0.f, 0.f}, { -TILE_LENGTH, TREE_HEIGHT, -TILE_LENGTH },
	{0.f, 1.f}, { -TILE_LENGTH, TREE_TOP_HEIGHT, -TILE_LENGTH },
	{1.f, 1.f}, { TILE_LENGTH, TREE_TOP_HEIGHT, -TILE_LENGTH },
	{1.f, 0.f}, { TILE_LENGTH, TREE_HEIGHT, -TILE_LENGTH },
	{ 0.f, 1.f, 0.f }, // Top
	{0.f, 0.f}, { -TILE_LENGTH, TREE_TOP_HEIGHT, -TILE_LENGTH },
	{1.f, 0.f}, { TILE_LENGTH, TREE_TOP_HEIGHT, -TILE_LENGTH },
	{1.f, 1.f}, { TILE_LENGTH, TREE_TOP_HEIGHT, TILE_LENGTH },
	{0.f, 1.f}, { -TILE_LENGTH, TREE_TOP_HEIGHT, TILE_LENGTH },
	{ 0.f, -1.f, 0.f }, // Bottom
	{0.f, 0.f}, { -TILE_LENGTH, TREE_HEIGHT, -TILE_LENGTH },
	{1.f, 0.f}, { TILE_LENGTH, TREE_HEIGHT, -TILE_LENGTH },
	{1.f, 1.f}, { TILE_LENGTH, TREE_HEIGHT, TILE_LENGTH },
	{0.f, 1.f}, { -TILE_LENGTH, TREE_HEIGHT, TILE_LENGTH },
	{ 1.f, 0.f, 0.f }, // Right
	{0.f, 0.f}, { TILE_LENGTH, TREE_HEIGHT, -TILE_LENGTH },
	{1.f, 0.f}, { TILE_LENGTH, TREE_TOP_HEIGHT, -TILE_LENGTH },
	{1.f, 1.f}, { TILE_LENGTH, TREE_TOP_HEIGHT, TILE_LENGTH },
	{0.f, 1.f}, { TILE_LENGTH, TREE_HEIGHT, TILE_LENGTH },
	{ -1.f, 0.f, 0.f }, // Left
	{0.f, 0.f}, { -TILE_LENGTH, TREE_HEIGHT, -TILE_LENGTH },
	{1.f, 0.f}, { -TILE_LENGTH, TREE_TOP_HEIGHT, -TILE_LENGTH },
	{1.f, 1.f}, { -TILE_LENGTH, TREE_TOP_HEIGHT, TILE_LENGTH },
	{0.f, 1.f}, { -TILE_LENGTH, TREE_HEIGHT, TILE_LENGTH }
};

// Coin
const vector<char> COMMANDS_COIN_OBJECT = {
		'C',
		'N', 'T', 'V', 'T', 'V', 'T', 'V', 'T', 'V',
		'N', 'T', 'V', 'T', 'V', 'T', 'V', 'T', 'V',
		'N', 'T', 'V', 'T', 'V', 'T', 'V', 'T', 'V',
		'N', 'T', 'V', 'T', 'V', 'T', 'V', 'T', 'V',
		'N', 'T', 'V', 'T', 'V', 'T', 'V', 'T', 'V',
		'N', 'T', 'V', 'T', 'V', 'T', 'V', 'T', 'V'
};
const vector<vector<float>> DATA_COIN_OBJECT = {
	{246.0f/255.0f, 192.0f/255.0f, 22.0f/255.0f, 1.f}, // BACK
	{ 0.f, 0.f, 1.f }, // Down
	{0.f, 0.f}, {-TILE_LENGTH, -TILE_LENGTH, TILE_LENGTH},
	{1.f, 0.f}, {TILE_LENGTH, -TILE_LENGTH, TILE_LENGTH},
	{1.f, 1.f}, {TILE_LENGTH, TILE_LENGTH, TILE_LENGTH},
	{0.f, 1.f}, {-TILE_LENGTH, TILE_LENGTH, TILE_LENGTH},
	{ 0.f, 0.f, -1.f }, // Up
	{0.f, 0.f}, {-TILE_LENGTH, -TILE_LENGTH, -TILE_LENGTH},
	{1.f, 0.f}, {TILE_LENGTH, -TILE_LENGTH, -TILE_LENGTH},
	{1.f, 1.f}, {TILE_LENGTH, TILE_LENGTH, -TILE_LENGTH},
	{0.f, 1.f}, {-TILE_LENGTH, TILE_LENGTH, -TILE_LENGTH},
	{ 0.f, 1.f, 0.f }, // Top
	{0.f, 0.f}, {-TILE_LENGTH, TILE_LENGTH, -TILE_LENGTH},
	{1.f, 0.f}, {TILE_LENGTH, TILE_LENGTH, -TILE_LENGTH},
	{1.f, 1.f}, {TILE_LENGTH, TILE_LENGTH, TILE_LENGTH},
	{0.f, 1.f}, {-TILE_LENGTH, TILE_LENGTH, TILE_LENGTH},
	{ 0.f, -1.f, 0.f }, // Bottom
	{0.f, 0.f}, {-TILE_LENGTH, -TILE_LENGTH, -TILE_LENGTH},
	{1.f, 0.f}, {TILE_LENGTH, -TILE_LENGTH, -TILE_LENGTH},
	{1.f, 1.f}, {TILE_LENGTH, -TILE_LENGTH, TILE_LENGTH},
	{0.f, 1.f}, {-TILE_LENGTH, -TILE_LENGTH, TILE_LENGTH},
	{ 1.f, 0.f, 0.f }, // Right
	{0.f, 0.f}, {TILE_LENGTH, -TILE_LENGTH, -TILE_LENGTH},
	{1.f, 0.f}, {TILE_LENGTH, TILE_LENGTH, -TILE_LENGTH},
	{1.f, 1.f}, {TILE_LENGTH, TILE_LENGTH, TILE_LENGTH},
	{0.f, 1.f}, {TILE_LENGTH, -TILE_LENGTH, TILE_LENGTH},
	{ -1.f, 0.f, 0.f }, // Left
	{0.f, 0.f}, {-TILE_LENGTH, -TILE_LENGTH, -TILE_LENGTH},
	{1.f, 0.f}, {-TILE_LENGTH, TILE_LENGTH, -TILE_LENGTH},
	{1.f, 1.f}, {-TILE_LENGTH, TILE_LENGTH, TILE_LENGTH},
	{0.f, 1.f}, {-TILE_LENGTH, -TILE_LENGTH, TILE_LENGTH}
};

#endif
