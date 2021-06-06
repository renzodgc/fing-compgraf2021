#pragma once
#ifndef COLORS_H
#define COLORS_H

struct Color {
	float red;
	float blue;
	float green;
	float alpha;
};

// COLORS
// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
const Color BLACK = { 0.f, 0.f, 0.f, 1.f }; // RGBA
const Color WHITE = { 1.f, 1.f, 1.f, 1.f }; // RGBA
const Color RED = { 1.f, 0.f, 0.f, 1.f }; // RGBA
const Color BLUE = { 0.f, 1.f, 0.f, 1.f }; // RGBA
const Color GREEN = { 0.f, 0.f, 1.f, 1.f }; // RGBA
const Color CYAN = { 0.f, 1.f, 1.f, 1.f }; // RGBA
const Color MAGENTA = { 1.f, 0.f, 1.f, 1.f }; // RGBA
const Color YELLOW = { 1.f, 1.f, 0.f, 1.f }; // RGBA
const Color LIGHT_GREY = { 0.3f, 0.3f, 0.3f, 1.f }; // RGBA

#endif
