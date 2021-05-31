#pragma once
#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

// DEPENDENCIES
// -----------------------------------------------------------------------------------


// NAMESPACE
// -----------------------------------------------------------------------------------
using namespace std;

// CLASS DEFINITION
// -----------------------------------------------------------------------------------

class Scene {

    private:
        // Singleton
        Scene();

    public:
        // Constructor and singleton method
        Scene(Scene const&) = delete;
        void operator=(Scene const&) = delete;
        static Scene& get_instance();

};

#endif
