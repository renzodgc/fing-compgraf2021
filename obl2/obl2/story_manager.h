#pragma once
#ifndef STORY_MANAGER_H
#define STORY_MANAGER_H

// DEPENDENCIES
// -----------------------------------------------------------------------------------

// C++ libraries
#include <iostream>
#include <string>
#include <ctime>
// Constants
#include "routes.h"
// Structures
#include "image.h"
// Helpers
#include "file_helper.h"

// CLASS DEFINITION
// -----------------------------------------------------------------------------------

class Story {

    private:

        // Singleton
        Story();

        // Main properties
        bool created;
        string current_directory;
        string current_directory_path;

        // Aux methods
        string get_current_time();

    public:

        // Constructor and singleton method
        Story(Story const&) = delete;
        void operator=(Story const&) = delete;
        static Story& get_instance();

        // Getters & Setters
        bool is_created();

        // Main methods
        bool create_current_directory();
        bool save_result(Image* result, ImageIs type);
};

#endif
#pragma once
