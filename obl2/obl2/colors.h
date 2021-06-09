#pragma once
#ifndef COLORS_H
#define COLORS_H

struct Color {
	double red;
	double blue;
	double green;
	double alpha;
};

// COLORS
// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
const Color BLACK = { 0., 0., 0., 1. }; // RGBA
const Color WHITE = { 1., 1., 1., 1. }; // RGBA
const Color RED = { 1., 0., 0., 1. }; // RGBA
const Color BLUE = { 0., 1., 0., 1. }; // RGBA
const Color GREEN = { 0., 0., 1., 1. }; // RGBA
const Color CYAN = { 0., 1., 1., 1. }; // RGBA
const Color MAGENTA = { 1., 0., 1., 1. }; // RGBA
const Color YELLOW = { 1., 1., 0., 1. }; // RGBA
const Color LIGHT_GREY = { 0.3, 0.3, 0.3, 1. }; // RGBA

#endif
