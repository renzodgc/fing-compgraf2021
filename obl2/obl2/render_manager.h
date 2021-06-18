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

enum class ImageIs {
    FullResult,
    ColorAmbient, ColorDiffuse, ColorSpecular,
    Ambient, Diffuse, Specular, Reflection, Transmission
};

class Render {

private:
    // Singleton
    Render();

    Color trace_rr(Ray ray, int depth, ImageIs type);
    Color shadow_rr(Object* object, Ray ray, Vector intersection_point, Vector norm, int depth, ImageIs type);
    tuple<int, float> get_closest_intersected_object(Ray ray); // index, distance
    tuple<vector<int>, vector<float>> Render::get_all_intersected_objects(Ray ray); // List of indexes, list of distances
    Color coef_trace_rr(Ray ray, ImageIs type);

    Color get_ambient_component(Object* object, ImageIs type);
    Color get_lights_component(Object* object, Ray ray, Vector intersection_point, Vector norm, ImageIs type);
    Color get_diffuse_component(Object* object, Ray ray, Vector intersection_point, Vector norm, ImageIs type, Ray shadow_ray);
    Color get_specular_component(Object* object, Ray ray, Vector intersection_point, Vector norm, ImageIs type, Ray shadow_ray);
    Color get_transmission_component(Object* object, Ray ray, Vector intersection_point, Vector norm, int depth, ImageIs type);
    Color get_reflective_component(Object* object, Ray ray, Vector intersection_point, Vector norm, int depth, ImageIs type);

public:
    // Constructor and singleton method
    Render(Render const&) = delete;
    void operator=(Render const&) = delete;
    static Render& get_instance();

    Image* ray_tracing(ImageIs type);
};

#endif
