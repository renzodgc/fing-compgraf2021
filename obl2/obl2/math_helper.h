#pragma once
#ifndef MATH_HELPER_H
#define MATH_HELPER_H

// DEPENDENCIES
// -----------------------------------------------------------------------------------

// C++ Libraries
#include <iostream>
#include <random>
#include <algorithm>
#include <iterator>
#include <vector>
#include <tuple>
#include <math.h>
// Constants
#include "colors.h"

// NAMESPACE
// -----------------------------------------------------------------------------------

using namespace std;

// HEADERS
// -----------------------------------------------------------------------------------

Color add_colors(Color a, Color b);

Color multiply_colors(Color a, Color b);

Color scale_color(Color a, float k);

#endif
