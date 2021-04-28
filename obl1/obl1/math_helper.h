#pragma once
#ifndef MATH_HELPER_H
#define MATH_HELPER_H

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
#include <math.h>

// NAMESPACE
// -----------------------------------------------------------------------------------
using namespace std;

// HEADERS
// -----------------------------------------------------------------------------------

position normalize_vector(position pos);

position cross_product_vector(position a, position b);

float degree_to_radian(float degree);

#endif