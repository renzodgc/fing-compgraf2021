#pragma once
#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H

// DEPENDENCIES
// -----------------------------------------------------------------------------------


// NAMESPACE
// -----------------------------------------------------------------------------------
using namespace std;

// CLASS DEFINITION
// -----------------------------------------------------------------------------------

class Render {

private:
    // Singleton
    Render();

public:
    // Constructor and singleton method
    Render(Render const&) = delete;
    void operator=(Render const&) = delete;
    static Render& get_instance();

};

#endif
#pragma once
