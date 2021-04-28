#pragma once
#ifndef MATH_HELPER_H
#define MATH_HELPER_H

// DEPENDENCIES
// -----------------------------------------------------------------------------------

#include <iostream>
#include <math.h>

#include "models.h"

// NAMESPACE
// -----------------------------------------------------------------------------------
using namespace std;

// HEADERS
// -----------------------------------------------------------------------------------

position normalize_vector(position pos);

position cross_product_vector(position a, position b);

float degree_to_radian(float degree);

#endif
