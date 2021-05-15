#pragma once
#ifndef MATH_HELPER_H
#define MATH_HELPER_H

// DEPENDENCIES
// -----------------------------------------------------------------------------------

#include <iostream>
#include <random>
#include <algorithm>
#include <iterator>
#include <vector>
#include <math.h>

#include "models.h"

// NAMESPACE
// -----------------------------------------------------------------------------------
using namespace std;

// HEADERS
// -----------------------------------------------------------------------------------

// Vector utils
position normalize_vector(position pos);
position cross_product_vector(position a, position b);
float degree_to_radian(float degree);

// Random utils
int get_random(int limit);
vector<int> get_random_vector(int length, int limit);

#endif
