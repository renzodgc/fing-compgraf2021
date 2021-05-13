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
#include "models.h"
#include "file_helper.h"

// NAMESPACE
// -----------------------------------------------------------------------------------
using namespace std;

// HEADERS
// -----------------------------------------------------------------------------------

class Draw {
private:
    Draw(); // Singleton

    vector<char>  player_commands;
    vector<vector<float>> player_data;
    GLuint player_texture;
public:
    Draw(Draw const&) = delete;
    void operator=(Draw const&) = delete;
    static Draw& get_instance();

    void player(bool use_texture);
    void lane(LaneIs laneType, bool use_texture);
    void tree(bool use_texture);
    void border(bool use_texture);

    void DrawMultiplePoints(GLenum primitive, vector<char> commands, vector<vector<float>> data, GLuint texture, bool use_texture);
    void DrawMultiplePoints(GLenum primitive, vector<char> commands, vector<vector<float>> data);
    void DrawHUD(HUDComponent left, HUDComponent right);
    void DrawHUDComponent(HUDComponent component);

    void DrawTexturedSquare(GLuint texture, textured_square square);
    void DrawReferenceObject();
};

#endif
