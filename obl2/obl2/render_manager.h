#pragma once
#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H

// DEPENDENCIES
// -----------------------------------------------------------------------------------

// C++ libraries
#include <iostream>
#include <algorithm>    // std::max
#include <vector>
#include <tuple>
// Constants
#include "colors.h"
#include "parameters.h"
// Structures
#include "image.h"
#include "polygon.h"
// Models
#include "ray.h"
#include "camera.h"
#include "light.h"
#include "object.h"
// Helpers
#include "math_helper.h"
// Managers
#include "scene_manager.h"

// NAMESPACE
// -----------------------------------------------------------------------------------
using namespace std;

// CLASS DEFINITION
// -----------------------------------------------------------------------------------

class Render {

    private:

        // Singleton
        Render();

        // Main methods
        Color trace_rr(Ray* ray, int depth, ImageIs type);
        Color coef_trace_rr(Ray* ray, ImageIs type);
        Color shadow_rr(Object* object, Ray* ray, Vector intersection_point, Vector norm, int depth, ImageIs type);

        // Aux methods
        tuple<int, float> get_closest_intersected_object(Ray* ray); // index, distance
        tuple<vector<int>, vector<float>> Render::get_all_intersected_objects(Ray* ray); // List of indexes, list of distances

        // Aux methods - intermediate results
        Color get_ambient_component(Object* object, ImageIs type);
        Color get_lights_component(Object* object, Ray* ray, Vector intersection_point, Vector norm, ImageIs type);
        Color get_diffuse_component(Object* object, Ray* ray, Vector intersection_point, Vector norm, ImageIs type, Ray* shadow_ray);
        Color get_specular_component(Object* object, Ray* ray, Vector intersection_point, Vector norm, ImageIs type, Ray* shadow_ray);
        Color get_transmission_component(Object* object, Ray* ray, Vector intersection_point, Vector norm, int depth, ImageIs type);
        Color get_reflective_component(Object* object, Ray* ray, Vector intersection_point, Vector norm, int depth, ImageIs type);

    public:

        // Constructor and singleton method
        Render(Render const&) = delete;
        void operator=(Render const&) = delete;
        static Render& get_instance();

        // Main methods
        Image* ray_tracing(ImageIs type, bool anti_aliasing);
};

#endif
