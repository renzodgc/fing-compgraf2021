#pragma once
#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

// DEPENDENCIES
// -----------------------------------------------------------------------------------

#include <iostream>
#include <vector>

#include "tinyxml2.h"
#include "camera.h"
#include "light.h"
#include "object.h"
#include "routes.h"

// NAMESPACE
// -----------------------------------------------------------------------------------

using namespace tinyxml2;

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

        // Aux properties
        bool loaded;
        unsigned int object_counter;

        // Aux methods
        bool load_camera(XMLElement* xmlCamera);
        bool load_light(XMLElement* xmlLight);
        bool load_object(XMLElement* xmlObject);

    public:
        // Constructor and singleton method
        Scene(Scene const&) = delete;
        void operator=(Scene const&) = delete;
        static Scene& get_instance();

        // Getters & setters
        bool is_loaded();
        Camera* get_camera();
        vector<Light*> get_lights();
        vector<Object*> get_objects();

        // Main methods
        bool load_scene();
};

#endif
