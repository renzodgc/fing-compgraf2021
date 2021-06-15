#pragma once
#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H

// DEPENDENCIES
// -----------------------------------------------------------------------------------

#include <iostream>
#include <algorithm>    // std::max
#include <vector>
#include <tuple>
#include "colors.h"
#include "parameters.h"
#include "ray.h"
#include "image.h"
#include "camera.h"
#include "light.h"
#include "object.h"
#include "scene_manager.h"
#include "math_helper.h"

// NAMESPACE
// -----------------------------------------------------------------------------------
using namespace std;

// CLASS DEFINITION
// -----------------------------------------------------------------------------------

class Render {

private:
    // Singleton
    Render();

    Color trace_rr(Ray ray, int depth);
    Color shadow_rr(Object* object, Ray ray, Vector intersection_point, Vector norm, int depth);
    tuple<int, float> get_closest_intersected_object(Ray ray); // index, distance

public:
    // Constructor and singleton method
    Render(Render const&) = delete;
    void operator=(Render const&) = delete;
    static Render& get_instance();

    Image* ray_tracing();
};

#endif
