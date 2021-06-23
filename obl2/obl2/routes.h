#pragma once
#ifndef ROUTES_H
#define ROUTES_H

// DEPENDENCIES
// ---------------------------------------------------------------------------------------

#include <string>

// FILE ROUTES
// ---------------------------------------------------------------------------------------

const std::string CONFIG_FILE = "tests_config_full_scene_diffuse.xml";
const std::string SAVE_FOLDER = "results\\";

// FILE NAMES
// ---------------------------------------------------------------------------------------

// General result
const std::string RESULT_FILE = "result.png";
// Coefficients
const std::string COEF_AMBIENT_FILE = "coef_ambient.png";
const std::string COEF_DIFFUSE_FILE = "coef_diffuse.png";
const std::string COEF_SPECULAR_FILE = "coef_specular.png";
const std::string COEF_REFLECTION_FILE = "coef_reflection.png";
const std::string COEF_TRANSMISSION_FILE = "coef_transmission.png";
// Colors
const std::string COLOR_AMBIENT_FILE = "color_ambient.png";
const std::string COLOR_DIFFUSE_FILE = "color_diffuse.png";
const std::string COLOR_SPECULAR_FILE = "color_specular.png";

#endif

