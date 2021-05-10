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

    void player();
    static void DrawTexturedSquare(GLuint texture, textured_square square);
    static void DrawMultiplePoints(GLenum primitive, vector<char> commands, vector<vector<float>> data, GLuint texture, bool use_texture);
    static void DrawHUD(HUDComponent left, HUDComponent right);
    static void DrawHUDComponent(HUDComponent component);
    static void DrawCube();
    static void DrawReferenceObject();
    static void DrawLane(LaneIs laneType);
    static void DrawTree();
};

#endif
