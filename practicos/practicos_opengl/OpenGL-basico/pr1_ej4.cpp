#include "exercises.h"


int pr1_ej4() {
	// DOCUMENTATION
	cout << "Controles:" << endl;
	cout << " ESC         -> Salir" << endl;
	cout << " MOUSE CLICK -> Static/Translation Render" << endl;
	cout << " L           -> Toggle textures" << endl;

	// VARIABLES
	bool program_running = true;
	SDL_Event sdl_event;

	color clear_color = BLACK;
	position camera_eye = { 0.f, 0.f, 0.5f }; // XYZ

	bool translate = false;
	bool texture_on = true;
	float scale = 1.f;

	// INITIALIZE WINDOW
	SDL_Window* window;
	SDL_GLContext context;
	tie(window, context) = InitializeSDL("Pr1-Ej4", SCR_WIDTH, SCR_HEIGHT);

	glMatrixMode(GL_PROJECTION);
	glClearColor(clear_color.red, clear_color.green, clear_color.blue, clear_color.alpha);

	gluPerspective(45, SCR_WIDTH / (float)SCR_HEIGHT, 0.1, 100);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);

	// TEXTURES
	GLuint texture = LoadTexture("../practicos/pr1/opengl.png");
	float rectangle_aspect_ratio = 452 / 212.f;
	float scaleRectX = 452. / 512.f;
	float scaleRectY = 212. / 512.f;
	
	// RENDER LOOP
	do {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		gluLookAt(camera_eye.x, camera_eye.y, camera_eye.z, 0, 0, 0, 0, 1, 0);

		// RENDER
		
		// Linear Transformation
		if (translate) {
			glTranslatef(-1.5, 0., -6.);

			DrawMulticoloredTriangle({
				RED, BLUE, GREEN,
				{0., 1., 0.}, {-1., -1., 0.}, {1., -1., 0.}
			});

			glTranslatef(3, 0., 0.);

			if (texture_on) {
				glScalef(scaleRectX * scale, scaleRectY * scale, 0.0);
				DrawTexturedSquare(texture, {
					WHITE,
					{0.095703125f, 0.486328125f}, {-1., -1., 0.}, // Bottom Left
					{0.978515625f, 0.486328125f}, {1., -1., 0.}, // Bottom Right
					{0.978515625f, 0.900390625f}, {1., 1., 0.}, // Top Right
					{0.095703125f, 0.900390625f}, {-1., 1., 0.} // Top Right
				});
			}
			else {
				DrawSquare({
					CYAN,
					{-1., -1., 0.}, {1., -1., 0.}, {1., 1., 0.}, {-1., 1., 0.}
				});
			}
		}
		else {
			DrawMulticoloredTriangle({
				CYAN, MAGENTA, YELLOW,
				{-1.5, 1., -6.}, {-2.5, -1., -6.}, {-0.5, -1., -6.}
			});

			if (texture_on) {
				DrawTexturedSquare(texture, {
					WHITE,
					{0., 0.}, {0.5, -1., -6.}, // Bottom Left
					{1., 0.}, {2.5, -1., -6.}, // Bottom Right
					{1., 1.}, {2.5, 1., -6.}, // Top Right
					{0., 1.}, {0.5, 1., -6.} // Top Right
				});
			}
			else {
				DrawSquare({
					WHITE,
					{0.5, -1., -6.}, {2.5, -1., -6.}, {2.5, 1., -6.}, {0.5, 1., -6.}
				});
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
				break;
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

