#pragma once
#ifndef FILE_HELPER_H
#define FILE_HELPER_H

// DEPENDENCIES
// -----------------------------------------------------------------------------------

// C++ Libraries
#include <iostream>
#include <string>
#include <windows.h>
// 3rd party libraries
#include "FreeImage.h"
// Constants
#include "routes.h"
// Structures
#include "image.h"

// HEADERS
// -----------------------------------------------------------------------------------

bool create_directory(string path);
bool save_image(Image* image, string file_name);

#endif
