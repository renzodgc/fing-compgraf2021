#pragma once
#ifndef STORY_MANAGER_H
#define STORY_MANAGER_H

// DEPENDENCIES
// -----------------------------------------------------------------------------------


// NAMESPACE
// -----------------------------------------------------------------------------------
using namespace std;

// CLASS DEFINITION
// -----------------------------------------------------------------------------------

class Story {

private:
    // Singleton
    Story();

public:
    // Constructor and singleton method
    Story(Story const&) = delete;
    void operator=(Story const&) = delete;
    static Story& get_instance();

    // TODO: Generate images and intermediate images
};

#endif
#pragma once
