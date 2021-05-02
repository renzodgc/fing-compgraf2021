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
	{-1.0f, -1.0f, 0.f}, {1.0f, -1.0f, 0.f}, {1.0f, 1.0f, 0.f}, {-1.0f, 1.0f, 0.f},
	{0.f, 1.f, 0.f, 1.f},
	{0.f, -1.0f, -1.0f}, {0.f, -1.0f, 1.0f}, {0.f, 1.0f, 1.0f}, {0.f, 1.0f, -1.0f},
	{0.f, 0.f, 1.f, 1.f},
	{-1.0f, 0.f, -1.0f}, {1.0f, 0.f, -1.0f}, {1.0f, 0.f, 1.0f}, {-1.0f, 0.f, 1.0f}
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
	{1.f, 0.f, 0.f, 1.f},
	{-1.0f, -1.0f, 1.f}, {1.0f, -1.0f, 1.f}, {1.0f, 1.0f, 1.f}, {-1.0f, 1.0f, 1.f},
	{1.f, 1.f, 0.f, 1.f},
	{-1.f, -1.0f, -1.0f}, {-1.f, 1.0f, -1.0f},  {1.f, 1.0f, -1.0f},  {1.f, -1.0f, -1.0f},
	{0.f, 1.f, 0.f, 1.f},
	{-1.f, 1.0f, -1.0f}, {-1.f, 1.0f, 1.0f},  {1.f, 1.0f, 1.0f},  {1.f, 1.0f, -1.0f},
	{0.f, 1.f, 1.f, 1.f},
	{-1.f, -1.0f, -1.0f}, {1.f, -1.0f, -1.0f},  {1.f, -1.0f, 1.0f},  {-1.f, -1.0f, 1.0f},
	{0.f, 0.f, 1.f, 1.f},
	{1.f, -1.0f, -1.0f}, {1.f, 1.0f, -1.0f},  {1.f, 1.0f, 1.0f},  {1.f, -1.0f, 1.0f},
	{1.f, 0.f, 1.f, 1.f},
	{-1.f, -1.0f, -1.0f}, {-1.f, -1.0f, 1.0f},  {-1.f, 1.0f, 1.0f},  {-1.f, 1.0f, -1.0f}
};

#endif
