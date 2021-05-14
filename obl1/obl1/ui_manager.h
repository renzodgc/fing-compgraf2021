#pragma once
#ifndef UI_MANAGER_H
#define UI_MANAGER_H

// DEPENDENCIES
// -----------------------------------------------------------------------------------

#include <string> 
#include <iostream>
#include "SDL.h"
#include "SDL_opengl.h"
#include "SDL_ttf.h"
#include <GL/glu.h>

#include "constants.h"
#include "draw_manager.h"

// NAMESPACE
// -----------------------------------------------------------------------------------
using namespace std;

// CLASS DEFINITION
// -----------------------------------------------------------------------------------

class UI {

    private:
        // Singleton
        UI();
        
        // Basic properties
        TTF_Font* font;
        HUDComponent score;
        HUDComponent coins;
        Draw* draw_manager;

        // Basic methods
        void set_message_on_component(string message, HUDComponent* component);
    
    public:
        // Constructor and singleton method
        UI(UI const&) = delete;
        void operator=(UI const&) = delete;
        static UI& get_instance();

        // Main methods
        void draw();
        void clean_memory();

        // Setters
        void set_score(int score_number);
        void set_coins(int coins_number);

};

#endif
