#include "exercises.h"
#include "utils.h"
#include "SDL.h"
#include "SDL_opengl.h"
#include <iostream>
#include "FreeImage.h"
#include <stdio.h>
#include <conio.h>
#include <GL/glu.h>

using namespace std;

// SETTINGS
const unsigned int SCR_WIDTH = 640;
const unsigned int SCR_HEIGHT = 480;

int pr1_ej3() {
	// INITIALIZATION
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cerr << "[Error]: No se pudo iniciar SDL: " << SDL_GetError() << endl;
		exit(1);
	}

	// DOCUMENTATION
	cout << "Controles:" << endl;
	cout << " ESC		  -> Salir" << endl;
	cout << " MOUSE CLICK -> Static/Translation Render" << endl;

	// VARIABLES
	bool program_running = true;
	SDL_Event sdl_event;

	float clear_color_red = 0.03f;
	float clear_color_green = 0.0f;
	float clear_color_blue = 0.0f;
	float x = 0.0f;
	float y = 0.0f;
	float z = 7.0f;

	bool translate = false;

	// WINDOW
	SDL_Window* window = SDL_CreateWindow(
		"Pr1-Ej3",
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

	gluPerspective(45, SCR_WIDTH / (float)SCR_HEIGHT, 0.1, 100);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);

	// RENDER LOOP
	do {
		glClearColor(clear_color_red, clear_color_green, clear_color_blue, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		gluLookAt(x, y, z, 0, 0, 0, 0, 1, 0);

		// RENDER
		glBegin(GL_TRIANGLES);
			glColor3f(1., 0., 0.);
			glVertex3f(-1.5, 1., -6.);
			glColor3f(0., 1., 0.);
			glVertex3f(-2.5, -1., -6.);
			glColor3f(0., 0., 1.);
			glVertex3f(-0.5, -1., -6.);
		glEnd();
		glPopMatrix();

		glBegin(GL_QUADS);
			glColor3f(1., 1., 1.);
			glVertex3f(0.5, 1., -6.);
			glVertex3f(2.5, 1., -6.);
			glVertex3f(2.5, -1., -6.);
			glVertex3f(0.5, -1., -6.);
		glEnd();
		glPopMatrix();

		// Linear Transformation
		if (translate) {
			glTranslatef(-1.5, 0., -6.);

			glBegin(GL_TRIANGLES);
				glColor3f(1., 0., 0.);
				glVertex3f(0., 1., 0.);
				glColor3f(1., 1., 0.);
				glVertex3f(-1., -1., 0.);
				glColor3f(1., 0., 1.);
				glVertex3f(1., -1., 0.);
			glEnd();
			glPopMatrix();

			glTranslatef(3, 0., 0.);

			glBegin(GL_QUADS);
				glColor3f(0., 1., 1.);
				glVertex3f(-1., 1., 0.);
				glVertex3f(1., 1., 0.);
				glVertex3f(1., -1., 0.);
				glVertex3f(-1., -1., 0.);
			glEnd();
			glPopMatrix();
		}


		// INPUT EVENT HANDLING
		while (SDL_PollEvent(&sdl_event)) {
			switch (sdl_event.type) {
			case SDL_MOUSEBUTTONDOWN:
				translate = !translate;
				break;
			case SDL_QUIT:
				program_running = false;
				break;
			case SDL_KEYUP:
				switch (sdl_event.key.keysym.sym) {
				case SDLK_ESCAPE:
					program_running = false;
					break;
				case SDLK_F11:
					ToggleFullscreen(window);
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

