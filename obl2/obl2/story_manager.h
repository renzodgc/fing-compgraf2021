#pragma once
#ifndef STORY_MANAGER_H
#define STORY_MANAGER_H

// DEPENDENCIES
// -----------------------------------------------------------------------------------

#include <iostream>
#include <string>
#include <ctime>
#include "file_helper.h"
#include "routes.h"
#include "image.h"
#include "render_manager.h"

// CLASS DEFINITION
// -----------------------------------------------------------------------------------

class Story {

private:
    // Singleton
    Story();

    // Main properties
    bool created;
    string current_directory;
    string directory_path;

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
    bool save_result(Image* result);
};

#endif
#pragma once
