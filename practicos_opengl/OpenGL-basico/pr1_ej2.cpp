#include "exercises.h"


int pr1_ej2() {
	// DOCUMENTATION
	cout << "Controles:" << endl;
	cout << " ESC		  -> Salir" << endl;
	cout << " MOUSE CLICK -> Static/Translation Render" << endl;

	// VARIABLES
	bool program_running = true;
	SDL_Event sdl_event;

	color clear_color = BLACK;
	position camera_eye = { 0.f, 0.f, 7.f }; // XYZ
	triangle tri;
	square sq;

	bool translate = false;

	// INITIALIZE WINDOW
	SDL_Window* window;
	SDL_GLContext context;
	tie(window, context) = InitializeSDL("Pr2-Ej1", SCR_WIDTH, SCR_HEIGHT);

	glMatrixMode(GL_PROJECTION);
	glClearColor(clear_color.red, clear_color.green, clear_color.blue, clear_color.alpha);
	
	gluPerspective(45, SCR_WIDTH / (float)SCR_HEIGHT, 0.1, 100);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);

	// RENDER LOOP
	do {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		gluLookAt(camera_eye.x, camera_eye.y, camera_eye.z, 0, 0, 0, 0, 1, 0);

		// RENDER
		

		// Linear Transformation
		if (translate) {
			glTranslatef(-1.5, 0., -6.);

			tri = {
				WHITE,
				{0., 1., 0.}, {-1., -1., 0.}, {1., -1., 0.}
			};
			DrawTriangle(tri);

			glTranslatef(3, 0., 0.);

			sq = {
				WHITE,
				{-1., -1., 0.}, {1., -1., 0.}, {1., 1., 0.}, {-1., 1., 0.}
			};
			DrawSquare(sq);
		}
		else {
			tri = {
				WHITE,
				{-1.5, 1., -6.}, {-2.5, -1., -6.}, {-0.5, -1., -6.}
			};
			DrawTriangle(tri);

			sq = {
				WHITE,
				{0.5, -1., -6.}, {2.5, -1., -6.}, {2.5, 1., -6.}, {0.5, 1., -6.}
			};
			DrawSquare(sq);
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
