#pragma once
#ifndef WINDOW_HELPER_H
#define WINDOW_HELPER_H

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

tuple<SDL_Window*, SDL_GLContext> InitializeSDL(string program_name, int scr_width, int scr_height);

void ToggleFullscreen(SDL_Window* Window);

#endif