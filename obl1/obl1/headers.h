#pragma once
#ifndef HEADERS_H
#define HEADERS_H

// DEPENDENCIES
// -----------------------------------------------------------------------------------

// External
#include <chrono>
#include <ctime>
#include <conio.h>
#include <ratio>
#include <stdio.h>

// Generic
#include "constants.h"
#include "models.h"

// Helpers
#include "camera_helper.h"
#include "draw_helper.h"
#include "file_helper.h"
#include "math_helper.h"
#include "window_helper.h"

// NAMESPACE
// -----------------------------------------------------------------------------------
using namespace std;

// HEADERS
// -----------------------------------------------------------------------------------

int game();

#endif