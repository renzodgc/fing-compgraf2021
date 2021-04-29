#pragma once
#ifndef MODELS_H
#define MODELS_H

enum class CameraType { isometric, third_person, free_view };

struct color {
	float red;
	float blue;
	float green;
	float alpha;
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

struct camera {
	position camera_eye;   // Specifies the position of the eye point.
	position camera_front; // Specifies the position of the reference point.
	position camera_up;    // Specifies the direction of the up vector.
	float yaw;
	float pitch;
};

struct triangle {
	color color;
	position a;
	position b;
	position c;
};

struct multicolored_triangle {
	color color_a;
	color color_b;
	color color_c;
	position a;
	position b;
	position c;
};

struct square {
	color color;
	position a;
	position b;
	position c;
	position d;
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
