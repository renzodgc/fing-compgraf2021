#pragma once
#ifndef MODELS_H
#define MODELS_H

#include "SDL.h"
#include "SDL_opengl.h"
#include "SDL_ttf.h"
#include <GL/glu.h>


enum class HUDComponentIs { left, right };

struct HUDComponent {
	HUDComponentIs position;
	SDL_Surface* surface_message;
	SDL_Surface* rgb_surface;
	int width;
	int height;
	GLuint texture_id;
	SDL_Color message_color;
};

struct color {
	float red;
	float blue;
	float green;
	float alpha;
};

struct vector3d {
	float x;
	float y;
	float z;
};

struct position {
	float x;
	float y;
	float z;
};

struct position2d {
	float x;
	float y;
};

struct textured_square {
	color color;
	position2d tex_a;
	position a;
	position2d tex_b;
	position b;
	position2d tex_c;
	position c;
	position2d tex_d;
	position d;
};

#endif
