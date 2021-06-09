#pragma once
#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

// DEPENDENCIES
// -----------------------------------------------------------------------------------

#include <vector>
#include "camera.h"
#include "light.h"
#include "object.h"

// NAMESPACE
// -----------------------------------------------------------------------------------

using namespace std;

// CLASS DEFINITION
// -----------------------------------------------------------------------------------

class Scene {

    private:
        // Singleton
        Scene();

        // Main objects
        Camera* camera;
        vector<Light*> lights;
        vector<Object*> objects;

    public:
        // Constructor and singleton method
        Scene(Scene const&) = delete;
        void operator=(Scene const&) = delete;
        static Scene& get_instance();

        // Getters & setters
        Camera* get_camera();
        vector<Light*> get_lights();
        vector<Object*> get_objects();

        // In charge of iterating through config_file from read_config
        void load_scene();
};

#endif
