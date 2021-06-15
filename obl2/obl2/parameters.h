#pragma once
#ifndef PARAMETERS_H
#define PARAMETERS_H

constexpr int IMAGE_WIDTH = 640;
constexpr int IMAGE_HEIGHT = 480;
constexpr int HALF_IMAGE_WIDTH = IMAGE_WIDTH/2;
constexpr int HALF_IMAGE_HEIGHT = IMAGE_HEIGHT/2;
constexpr int IMAGE_BITS_PER_PIXEL = 24; // 3 x 8 bit (RGB)

constexpr int MAX_DEPTH = 5;
constexpr float FOV = 100;

#endif
