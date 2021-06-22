#pragma once
#ifndef PARAMETERS_H
#define PARAMETERS_H

// GENERAL CONSTANTS
// ---------------------------------------------------------------------------------------

// Dimensions
constexpr int IMAGE_WIDTH = 1024;
constexpr int IMAGE_HEIGHT = 1024;
constexpr int HALF_IMAGE_WIDTH = IMAGE_WIDTH/2;
constexpr int HALF_IMAGE_HEIGHT = IMAGE_HEIGHT/2;
constexpr int IMAGE_BITS_PER_PIXEL = 24; // 3 x 8 bit (RGB)

// Ray tracing
constexpr int MAX_DEPTH = 3;
constexpr float FOV = 2500.f;
const bool ANTIALIASING = false;
const float ANTIALIASING_SHIFT = 0.25f;
constexpr float EPSILON = 0.005f;
constexpr float SPECULAR_EXPONENT = 64.f;
const float LIGHT_ATTENUATION_C0_ADDITION = 0.05f;
const float LIGHT_ATTENUATION_C1_MULTIPLIER = 150.f; // Scale up the attenuation ratio since our distances are in pixels

// Gamma correction
constexpr double GAMMA_CORRECTION = 0.667;

#endif
