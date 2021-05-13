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

// Helpers
#include "file_helper.h"
#include "math_helper.h"
#include "window_helper.h"

// Models
#include "models.h"

#include "lane_model.h"
#include "player_model.h"

// Managers
#include "camera_manager.h"
#include "draw_manager.h"
#include "ui_manager.h"

// NAMESPACE
// -----------------------------------------------------------------------------------
using namespace std;

// HEADERS
// -----------------------------------------------------------------------------------

int game();

#endif