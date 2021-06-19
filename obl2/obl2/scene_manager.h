#pragma once
#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

// DEPENDENCIES
// -----------------------------------------------------------------------------------

// C++ Libraries
#include <iostream>
#include <vector>
// 3rd party libraries
#include "tinyxml2.h"
// Constants
#include "routes.h"
// Structures
#include "polygon.h"
// Objects
#include "camera.h"
#include "light.h"
#include "object.h"
#include "sphere.h"
#include "cylinder.h"
#include "rectangle.h"
#include "mesh.h"

// NAMESPACE
// -----------------------------------------------------------------------------------

using namespace tinyxml2;

// CLASS DEFINITION
// -----------------------------------------------------------------------------------

class Scene {

    private:

        // Singleton
        Scene();

        // Main properties
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
        vector<Polygon*> load_mesh(XMLElement* xmlObject);
        Polygon* load_polygon(XMLElement* xmlObject);

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
