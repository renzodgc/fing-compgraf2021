#pragma once
#ifndef FILE_HELPER_H
#define FILE_HELPER_H

// DEPENDENCIES
// -----------------------------------------------------------------------------------

#include <string>
#include "FreeImage.h"
#include "routes.h"
#include "config.h"

// NAMESPACE
// -----------------------------------------------------------------------------------
using namespace std;

// HEADERS
// -----------------------------------------------------------------------------------


Config read_config();

void write_image();

#endif
