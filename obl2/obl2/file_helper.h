#pragma once
#ifndef FILE_HELPER_H
#define FILE_HELPER_H

// DEPENDENCIES
// -----------------------------------------------------------------------------------

#include <iostream>
#include <string>
#include <windows.h>
#include "FreeImage.h"
#include "routes.h"
#include "image.h"

// HEADERS
// -----------------------------------------------------------------------------------

bool create_directory(string path);
bool save_image(Image* image, string file_name);

#endif
