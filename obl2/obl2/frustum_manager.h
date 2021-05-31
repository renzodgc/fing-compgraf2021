#pragma once
#ifndef FRUSTUM_MANAGER_H
#define FRUSTUM_MANAGER_H

// Reference: http://www.lighthouse3d.com/tutorials/view-frustum-culling/

// DEPENDENCIES
// -----------------------------------------------------------------------------------

#include <iostream>
#include <stdio.h>
#include <math.h>

#include "SDL.h"
#include "SDL_opengl.h"
#include <GL/glu.h>

#include "constants.h"
#include "vector3.h"
#include "plane.h"

// NAMESPACE
// -----------------------------------------------------------------------------------
using namespace std;

// CLASS DEFINITION
// -----------------------------------------------------------------------------------

class FrustumGeometric {

private:
	// Singleton
	FrustumGeometric();

	enum {
		TOP = 0,
		BOTTOM,
		LEFT,
		RIGHT,
		NEARP,
		FARP
	};
public:
	// Constructor and singleton method
	FrustumGeometric(FrustumGeometric const&) = delete;
	void operator=(FrustumGeometric const&) = delete;
	static FrustumGeometric& get_instance();

	enum { OUTSIDE, INTERSECT, INSIDE };

	Plane planes[6];
	Vector3 near_top_left, near_top_right, near_bottom_left, near_bottom_right;
	Vector3 far_top_left, far_top_right, far_bottom_left, far_bottom_right;
	float near_distance, far_distance, ratio, angle, tang;
	float near_width, near_height, far_width, far_height;

	// Main methods
	int point_in_frustum(Vector3& point);
	int sphere_in_frustum(Vector3& point, float radio);

	// Draw methods
	void draw_points();
	void draw_lines();
	void draw_planes();
	void draw_normals();

	// Getters and Setters
	void FrustumGeometric::set_cam_internals(float angle, float ratio, float near_distance, float far_distance);
	void set_cam_def(Vector3& p, Vector3& l, Vector3& u);
};

#endif