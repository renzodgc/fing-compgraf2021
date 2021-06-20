#pragma once
#ifndef COLORS_H
#define COLORS_H

struct Color {
	double red;
	double green;
	double blue;
	double alpha;
};

// COLORS
// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

const Color BLACK = { 0., 0., 0., 1. }; // RGBA
const Color WHITE = { 1., 1., 1., 1. }; // RGBA
const Color RED = { 1., 0., 0., 1. }; // RGBA
const Color GREEN = { 0., 1., 0., 1. }; // RGBA
const Color BLUE = { 0., 0., 1., 1. }; // RGBA
const Color CYAN = { 0., 1., 1., 1. }; // RGBA
const Color YELLOW = { 1., 0., 1., 1. }; // RGBA
const Color MAGENTA = { 1., 1., 0., 1. }; // RGBA
const Color LIGHT_GREY = { 0.7, 0.7, 0.7, 1. }; // RGBA
const Color GREY = { 0.3, 0.3, 0.3, 1. }; // RGBA
const Color DARK_GREY = { 0.1, 0.1, 0.1, 1. }; // RGBA

// USED COLORS
// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

const Color BACKGROUND_COLOR = BLACK;
const Color AMBIENT_LIGHTING = GREY;

#endif
