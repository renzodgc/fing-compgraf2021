#pragma once
#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "models.h"

// SETTINGS
const unsigned int SCR_WIDTH = 1024;
const unsigned int SCR_HEIGHT = 768;

// COLORS
const color BLACK = { 0.f, 0.f, 0.f, 1.f }; // RGBA
const color WHITE = { 1.f, 1.f, 1.f, 1.f }; // RGBA
const color RED = { 1.f, 0.f, 0.f, 1.f }; // RGBA
const color BLUE = { 0.f, 1.f, 0.f, 1.f }; // RGBA
const color GREEN = { 0.f, 0.f, 1.f, 1.f }; // RGBA
const color CYAN = { 0.f, 1.f, 1.f, 1.f }; // RGBA
const color MAGENTA = { 1.f, 0.f, 1.f, 1.f }; // RGBA
const color YELLOW = { 1.f, 1.f, 0.f, 1.f }; // RGBA

// CAMERA
const double MOVEMENT_CAMERA_SPEED = 0.005;
const float MOUSE_SENSITIVITY = 0.1f;

#endif
