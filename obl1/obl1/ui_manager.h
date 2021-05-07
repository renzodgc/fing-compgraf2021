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

// HEADERS
// -----------------------------------------------------------------------------------

class UI {
private:
    TTF_Font* font;
    HUDComponent score;
    HUDComponent coins;

    void set_message_on_component(string message, HUDComponent* component);
public:
    UI();
    ~UI();

    void draw();
    void set_score(int score_number);
    void set_coins(int coins_number);
};

#endif
