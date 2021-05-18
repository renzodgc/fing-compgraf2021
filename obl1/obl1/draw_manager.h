#pragma once
#ifndef DRAW_MANAGER_H
#define DRAW_MANAGER_H

// DEPENDENCIES
// -----------------------------------------------------------------------------------

#include <iostream>
#include <vector>

#include "SDL.h"
#include "SDL_opengl.h"
#include <GL/glu.h>

#include "constants.h"
#include "gl_constants.h"
#include "models.h"
#include "file_helper.h"

// NAMESPACE
// -----------------------------------------------------------------------------------
using namespace std;

// CLASS DEFINITION
// -----------------------------------------------------------------------------------

class Draw {
    
    private:
        // Singleton
        Draw();

        // Basic properties
        vector<char>  player_commands;
        vector<vector<float>> player_data;
        GLuint player_texture;
        vector<char>  car_commands;
        vector<vector<float>> car_data;
        GLuint car_texture;
        GLuint grass_texture;
        GLuint street_texture;
        GLuint wood_texture;
        GLuint leaves_texture;
        GLuint keybinds_texture;
    public:
        // Constructor and singleton method
        Draw(Draw const&) = delete;
        void operator=(Draw const&) = delete;
        static Draw& get_instance();

        // Main objects' drawing methods
        void player(bool use_texture);
        void lane(LaneIs laneType, bool use_texture);
        void tree(bool use_texture);
        void border(bool use_texture);
        void car(bool use_texture);

        // Primitive objects' drawing methods
        void DrawMultiplePoints(GLenum primitive, vector<char> commands, vector<vector<float>> data, GLuint texture, bool use_texture);
        void DrawMultiplePoints(GLenum primitive, vector<char> commands, vector<vector<float>> data);
        void DrawHUD(HUDComponent top_left, HUDComponent top_right, HUDComponent top_center);
        void DrawHUDComponent(HUDComponent component);
};

#endif
