#pragma once
#ifndef UTILS_H
#define UTILS_H

#include "models.h"
#include "SDL.h"
#include "SDL_opengl.h"
#include <iostream>
#include "FreeImage.h"
#include <stdio.h>
#include <conio.h>
#include <GL/glu.h>
#include <tuple>
#include <ctime>
#include <ratio>
#include <chrono>

using namespace std;

tuple<SDL_Window*, SDL_GLContext> InitializeSDL(string program_name, int scr_width, int scr_height);

void ToggleFullscreen(SDL_Window* Window);

GLuint LoadTexture(string texture_file);

void DrawTriangle(triangle triangle);

void DrawMulticoloredTriangle(multicolored_triangle triangle);

void DrawSquare(square square);

void DrawTexturedSquare(GLuint texture, textured_square square);

#endif