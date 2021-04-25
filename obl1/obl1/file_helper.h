#pragma once
#ifndef FILE_HELPER_H
#define FILE_HELPER_H

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

GLuint LoadTexture(string texture_file);

tuple<vector<char>, vector<vector<float>>> LoadTrianglePolygonFile(string texture_file);

#endif