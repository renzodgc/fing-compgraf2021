#pragma once
#ifndef DRAW_MANAGER_H
#define DRAW_MANAGER_H

// DEPENDENCIES
// -----------------------------------------------------------------------------------

#include <iostream>
#include <vector>

#include "SDL.h"
#include "SDL_opengl.h"
#include <GL/glu.h>

#include "constants.h"
#include "models.h"

// NAMESPACE
// -----------------------------------------------------------------------------------
using namespace std;

// HEADERS
// -----------------------------------------------------------------------------------

void DrawTexturedSquare(GLuint texture, textured_square square);

void DrawMultiplePoints(GLenum primitive, vector<char> commands, vector<vector<float>> data);

void DrawHUD(HUDComponent left, HUDComponent right);

void DrawHUDComponent(HUDComponent component);

void DrawCube();

void DrawReferenceObject();

void DrawLane(LaneIs laneType);

#endif