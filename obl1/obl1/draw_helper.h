#pragma once
#ifndef DRAW_HELPER_H
#define DRAW_HELPER_H

// DEPENDENCIES
// -----------------------------------------------------------------------------------

#include "models.h"
#include "SDL.h"
#include "SDL_opengl.h"
#include <iostream>
#include "FreeImage.h"
#include <stdio.h>
#include <conio.h>
#include <GL/glu.h>
#include <tuple>
#include <ctime>
#include <ratio>
#include <chrono>
#include <vector>
#include <fstream>

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