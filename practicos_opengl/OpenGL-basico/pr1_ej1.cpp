#include "exercises.h"
#include "SDL.h"
#include "SDL_opengl.h"
#include <iostream>
#include "FreeImage.h"
#include <stdio.h>
#include <conio.h>
#include <GL/glu.h>

using namespace std;

#define SDL_NUMERIC_MINUS 1073741910
#define SDL_NUMERIC_PLUS 1073741911

// SETTINGS
const unsigned int SCR_WIDTH = 640;
const unsigned int SCR_HEIGHT = 480;

int pr1_ej1() {
	// INITIALIZATION
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cerr << "[Error]: No se pudo iniciar SDL: " << SDL_GetError() << endl;
		exit(1);
	}

	// DOCUMENTATION
	cout << "Controles:" << endl;
	cout << "   R -> Incrementar Rojo" << endl;
	cout << "   G -> Incrementar Verde" << endl;
	cout << "   B -> Incrementar Azul" << endl;
	cout << "   + -> Incrementar Blanco" << endl;
	cout << "   - -> Decrementar Blanco" << endl;
	cout << " ESC -> Salir" << endl;
	

	// VARIABLES
	bool program_running = true;
	SDL_Event sdl_event;

	float clear_color_red = 0.3f;
	float clear_color_green = 0.3f;
	float clear_color_blue = 0.3f;

	// WINDOW
	SDL_Window* window = SDL_CreateWindow(
		"Pr1-Ej1",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		SCR_WIDTH, SCR_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
	);
	if (window == NULL) {
		cerr << "[Video Error]: " << SDL_GetError() << endl;
		SDL_Quit();
		exit(1);
	}
	SDL_GLContext context = SDL_GL_CreateContext(window);
	if (window == NULL) {
		cerr << "[GL Context Error]: " << SDL_GetError() << endl;
		SDL_Quit();
		exit(1);
	}

	glMatrixMode(GL_PROJECTION);
	glClearColor(clear_color_red, clear_color_green, clear_color_blue, 1);

	// RENDER LOOP
	do {
		glClearColor(clear_color_red, clear_color_green, clear_color_blue, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		// RENDER
		

		// INPUT EVENT HANDLING
		while (SDL_PollEvent(&sdl_event)) {
			switch (sdl_event.type) {
			case SDL_QUIT:
				program_running = false;
				break;
			case SDL_KEYUP:
				// cout << sdl_event.key.keysym.sym << endl;
				switch (sdl_event.key.keysym.sym) {
				case SDLK_ESCAPE:
					program_running = false;
					break;
				case SDLK_r:
					clear_color_red = min(clear_color_red + 0.1f, 1.0f);
					break;
				case SDLK_g:
					clear_color_green = min(clear_color_green + 0.1f, 1.0f);
					break;
				case SDLK_b:
					clear_color_blue = min(clear_color_blue + 0.1f, 1.0f);
					break;
				case SDLK_PLUS:
				case SDL_NUMERIC_PLUS:
					clear_color_red = min(clear_color_red + 0.1f, 1.0f);
					clear_color_green = min(clear_color_green + 0.1f, 1.0f);
					clear_color_blue = min(clear_color_blue + 0.1f, 1.0f);
					break;
				case SDLK_MINUS:
				case SDL_NUMERIC_MINUS:
					clear_color_red = max(clear_color_red - 0.1f, 0.0f);
					clear_color_green = max(clear_color_green - 0.1f, 0.0f);
					clear_color_blue = max(clear_color_blue - 0.1f, 0.0f);
					break;
				}
			}
		}
		SDL_GL_SwapWindow(window);
	} while (program_running);

	// CLEANUP
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
