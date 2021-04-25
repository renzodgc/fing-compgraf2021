#pragma once
#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "models.h"

// SETTINGS
// 1024x576, 1152x648, 1280x720, 1366x768, 1600x900, 1920x1080
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;

// COLORS
const color BLACK = { 0.f, 0.f, 0.f, 1.f }; // RGBA
const color WHITE = { 1.f, 1.f, 1.f, 1.f }; // RGBA
const color RED = { 1.f, 0.f, 0.f, 1.f }; // RGBA
const color BLUE = { 0.f, 1.f, 0.f, 1.f }; // RGBA
const color GREEN = { 0.f, 0.f, 1.f, 1.f }; // RGBA
const color CYAN = { 0.f, 1.f, 1.f, 1.f }; // RGBA
const color MAGENTA = { 1.f, 0.f, 1.f, 1.f }; // RGBA
const color YELLOW = { 1.f, 1.f, 0.f, 1.f }; // RGBA

#endif
