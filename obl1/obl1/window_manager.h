#pragma once
#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

// DEPENDENCIES
// -----------------------------------------------------------------------------------

#include <iostream>
#include <tuple>

#include "SDL.h"
#include "SDL_opengl.h"
#include <GL/glu.h>

// NAMESPACE
// -----------------------------------------------------------------------------------
using namespace std;

// HEADERS
// -----------------------------------------------------------------------------------

tuple<SDL_Window*, SDL_GLContext> InitializeSDL(string program_name, int scr_width, int scr_height);

void ToggleFullscreen(SDL_Window* Window);

#endif