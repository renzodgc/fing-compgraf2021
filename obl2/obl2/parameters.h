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
constexpr int MAX_DEPTH = 6;
constexpr float FOV = 2500.f;
constexpr float EPSILON = 0.005f;

// Gamma correction
constexpr double GAMMA_CORRECTION = 0.667;

#endif
