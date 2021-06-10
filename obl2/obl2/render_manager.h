#pragma once
#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H

// DEPENDENCIES
// -----------------------------------------------------------------------------------

#include "colors.h"
#include "parameters.h"
#include "ray.h"
#include "image.h"

// NAMESPACE
// -----------------------------------------------------------------------------------
using namespace std;

// CLASS DEFINITION
// -----------------------------------------------------------------------------------

const Color BACKGROUND_COLOR = LIGHT_GREY;

class Render {

private:
    // Singleton
    Render();

    Color trace_rr(Ray ray, int depth);
    Color shadow_rr(short object, Ray ray, Vector point, float norm, int depth);

public:
    // Constructor and singleton method
    Render(Render const&) = delete;
    void operator=(Render const&) = delete;
    static Render& get_instance();

    Image ray_tracing();
};

#endif
#pragma once
