#pragma once
#ifndef FILE_HELPER_H
#define FILE_HELPER_H

// DEPENDENCIES
// -----------------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <tuple>
#include <vector>

#include "SDL.h"
#include "SDL_opengl.h"
#include "FreeImage.h"
#include <GL/glu.h>

// NAMESPACE
// -----------------------------------------------------------------------------------
using namespace std;

// HEADERS
// -----------------------------------------------------------------------------------

GLuint LoadTexture(string texture_file);

tuple<vector<char>, vector<vector<float>>> LoadTrianglePolygonFile(string texture_file);

#endif