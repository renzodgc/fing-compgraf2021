#pragma once
#ifndef FILE_HELPER_H
#define FILE_HELPER_H

// DEPENDENCIES
// -----------------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <tuple>
#include <vector>

#include "SDL.h"
#include "SDL_opengl.h"
#include "FreeImage.h"
#include <GL/glu.h>

#include "models.h"

// NAMESPACE
// -----------------------------------------------------------------------------------
using namespace std;

// HEADERS
// -----------------------------------------------------------------------------------

GLuint load_texture(string texture_file);

tuple<vector<char>, vector<vector<float>>> load_obj(string file, ObjType obj_type);

#endif
