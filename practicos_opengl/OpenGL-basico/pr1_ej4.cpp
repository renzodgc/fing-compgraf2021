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


int pr1_ej4() {
	// INITIALIZATION
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cerr << "[Error]: No se pudo iniciar SDL: " << SDL_GetError() << endl;
		exit(1);
	}

	// DOCUMENTATION
	cout << "Controles:" << endl;
	cout << " ESC         -> Salir" << endl;
	cout << " MOUSE CLICK -> Static/Translation Render" << endl;
	cout << " L           -> Toggle textures" << endl;

	// VARIABLES
	bool program_running = true;
	SDL_Event sdl_event;

	float clear_color_red = 0.0f;
	float clear_color_green = 0.0f;
	float clear_color_blue = 0.0f;
	float x = 0.0f;
	float y = 0.0f;
	float z = 7.0f;
	float scale = 1.f;

	bool texture_on = true;
	bool translate = false;

	// WINDOW
	SDL_Window* window = SDL_CreateWindow(
		"Pr1-Ej4",
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

	// TEXTURE
	string texture_file;
	texture_file = "../practicos/pr1/opengl.png";

	// Load texture's image
	FREE_IMAGE_FORMAT fif = FreeImage_GetFIFFromFilename(texture_file.c_str());
	FIBITMAP* bitmap = FreeImage_Load(fif, texture_file.c_str());
	bitmap = FreeImage_ConvertTo24Bits(bitmap);
	int texture_width = FreeImage_GetWidth(bitmap);
	int texture_height = FreeImage_GetHeight(bitmap);
	void* data = FreeImage_GetBits(bitmap);
	float rectangle_aspect_ratio = 452 / 212.f;
	float scaleRectX = 452. / 512.f;
	float scaleRectY = 212. / 512.f;

	// Apply texture
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture_width, texture_height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	
	// RENDER LOOP
	do {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		gluLookAt(x, y, z, 0, 0, 0, 0, 1, 0);

		// RENDER
		
		// Linear Transformation
		if (translate) {
			glTranslatef(-1.5, 0., -6.);

			glBegin(GL_TRIANGLES);
				glColor3f(1., 1., 0.);
				glVertex3f(0., 1., 0.);
				glColor3f(0., 1., 1.);
				glVertex3f(-1., -1., 0.);
				glColor3f(1., 0., 1.);
				glVertex3f(1., -1., 0.);
			glEnd();
			glPopMatrix();

			glTranslatef(3, 0., 0.);

			if (texture_on) {
				// source and dest are arbitrary rectangles.
				
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, texture);
				
				glScalef(scaleRectX * scale, scaleRectY * scale, 0.0);
				glBegin(GL_QUADS);
					glColor3f(1., 1., 1.);
					glTexCoord2f(0.095703125f, 0.486328125f); glVertex3f(-1., -1., 0.); // Bottom Left
					glTexCoord2f(0.978515625f, 0.486328125f); glVertex3f(1., -1., 0.); // Bottom Right
					glTexCoord2f(0.978515625f, 0.900390625f); glVertex3f(1, 1., 0.); // Top Right
					glTexCoord2f(0.095703125f, 0.900390625f); glVertex3f(-1, 1., 0.); // Top Right
				glEnd();
				glPopMatrix();
				glDisable(GL_TEXTURE_2D);
			}
			else {
				glBegin(GL_QUADS);
					glColor3f(0., 1., 1.);
					glVertex3f(-1., -1., 0.);
					glVertex3f(1., -1., 0.);
					glVertex3f(1., 1., 0.);
					glVertex3f(-1., 1., 0.);
					glEnd();
				glPopMatrix();
			}
		}
		else {
			glBegin(GL_TRIANGLES);
				glColor3f(1., 0., 0.); glVertex3f(-1.5, 1., -6.);
				glColor3f(0., 1., 0.); glVertex3f(-2.5, -1., -6.);
				glColor3f(0., 0., 1.); glVertex3f(-0.5, -1., -6.);
			glEnd();
			glPopMatrix();

			if (texture_on) {
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, texture);
				glBegin(GL_QUADS);
					glColor3f(1., 1., 1.);
					glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5, -1., -6.);
					glTexCoord2f(1.0f, 0.0f); glVertex3f(2.5, -1., -6.);
					glTexCoord2f(1.0f, 1.0f); glVertex3f(2.5, 1., -6.);
					glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5, 1., -6.);
				glEnd();
				glPopMatrix();
				glDisable(GL_TEXTURE_2D);
			}
			else {
				glBegin(GL_QUADS);
					glColor3f(1., 1., 1.);
					glVertex3f(0.5, 1., -6.);
					glVertex3f(2.5, 1., -6.);
					glVertex3f(2.5, -1., -6.);
					glVertex3f(0.5, -1., -6.);
				glEnd();
				glPopMatrix();
			}
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
				case SDLK_l:
					texture_on = !texture_on;
					break;
				case SDLK_UP:
					scale += 0.1f;
					break;
				case SDLK_DOWN:
					scale -= 0.1f;
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

