#pragma once
#ifndef DRAW_HELPER_H
#define DRAW_HELPER_H

// DEPENDENCIES
// -----------------------------------------------------------------------------------

#include <iostream>
#include <vector>

#include "SDL.h"
#include "SDL_opengl.h"
#include <GL/glu.h>

#include "models.h"

// NAMESPACE
// -----------------------------------------------------------------------------------
using namespace std;

// HEADERS
// -----------------------------------------------------------------------------------

void DrawTriangle(triangle triangle);

void DrawMulticoloredTriangle(multicolored_triangle triangle);

void DrawSquare(square square);

void DrawTexturedSquare(GLuint texture, textured_square square);

void DrawMultiplePoints(GLenum primitive, vector<char> commands, vector<vector<float>> data);

#endif