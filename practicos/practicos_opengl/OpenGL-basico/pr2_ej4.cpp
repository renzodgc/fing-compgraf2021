#include "exercises.h"

const double REFRESH_SPEED = 0.2; // Hz (1 turn / 5 seconds)

int pr2_ej4() {
	// DOCUMENTATION
	cout << "Controles:" << endl;
	cout << " ESC         -> Salir" << endl;

	// VARIABLES
	bool program_running = true;
	SDL_Event sdl_event;

	color clear_color = {0.3f, 0.3f, 0.3f, 1.f};
	position camera_eye = { 0.f, 0.f, 5.5f }; // XYZ

	float alpha = 0.3f;
	bool alpha_increasing = true;
	chrono::duration<double> delta_time;
	chrono::high_resolution_clock::time_point current_t, previous_t;

	// INITIALIZE WINDOW
	SDL_Window* window;
	SDL_GLContext context;
	tie(window, context) = InitializeSDL("Pr2-Ej3", SCR_WIDTH, SCR_HEIGHT);

	glMatrixMode(GL_PROJECTION);
	glClearColor(clear_color.red, clear_color.green, clear_color.blue, clear_color.alpha);

	gluPerspective(45, SCR_WIDTH / (float)SCR_HEIGHT, 0.1, 100);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);

	// INTIALIZE DATA

	vector<char> commands_horizontal_squares(8 * 5, 'V');
	vector<char> commands_vertical_squares(8 * 5, 'V');
	for (int i = 0; i < 8; i++) {
		commands_horizontal_squares[i * 5] = 'C';
		commands_vertical_squares[i * 5] = 'A';
	}

	vector<vector<float>> data_horizontal_squares(8 * 5, vector<float>(3, 0.f));
	vector<vector<float>> data_vertical_squares(8 * 5, vector<float>(4, 0.f));

	// Colors
	data_horizontal_squares[0] = { 0.f, 0.f, 0.f };
	data_horizontal_squares[5] = { 1.f, 0.f, 0.f };
	data_horizontal_squares[10] = { 0.f, 1.f, 0.f };
	data_horizontal_squares[15] = { 1.f, 1.f, 0.f };
	data_horizontal_squares[20] = { 0.f, 0.f, 1.f };
	data_horizontal_squares[25] = { 1.f, 0.f, 1.f };
	data_horizontal_squares[30] = { 0.f, 1.f, 1.f };
	data_horizontal_squares[35] = { 1.f, 1.f, 1.f };

	data_vertical_squares[0] = { 0.f, 0.f, 0.f, alpha };
	data_vertical_squares[5] = { 1.f, 0.f, 0.f, alpha };
	data_vertical_squares[10] = { 0.f, 1.f, 0.f, alpha };
	data_vertical_squares[15] = { 1.f, 1.f, 0.f, alpha };
	data_vertical_squares[20] = { 0.f, 0.f, 1.f, alpha };
	data_vertical_squares[25] = { 1.f, 0.f, 1.f, alpha };
	data_vertical_squares[30] = { 0.f, 1.f, 1.f, alpha };
	data_vertical_squares[35] = { 1.f, 1.f, 1.f, alpha };

	// Positions
	for (int i = 0; i < 8; i++) {
		data_horizontal_squares[(i * 5) + 1] = { -3.f, (float)(i), 0.f }; // Bottom Left
		data_horizontal_squares[(i * 5) + 2] = { 11.f, (float)(i), 0.f }; // Bottom Right
		data_horizontal_squares[(i * 5) + 3] = { 11.f, (float)(i + 1), 0.f }; // Top Right
		data_horizontal_squares[(i * 5) + 4] = { -3.f, (float)((i + 1)), 0.f }; // Top Left

		data_vertical_squares[(i * 5) + 1] = { (float)(i), -3.f, 0.1f, 0.f }; // Bottom Left
		data_vertical_squares[(i * 5) + 2] = { (float)(i + 1), -3.f, 0.1f, 0.f }; // Bottom Right
		data_vertical_squares[(i * 5) + 3] = { (float)(i + 1), 11.f, 0.1f, 0.f }; // Top Right
		data_vertical_squares[(i * 5) + 4] = { (float)(i), 11.f, 0.1f, 0.f }; // Top Left
	}

	previous_t = chrono::high_resolution_clock::now();
	// RENDER LOOP
	do {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		gluLookAt(camera_eye.x, camera_eye.y, camera_eye.z, 0, 0, 0, 0, 1, 0);

		current_t = chrono::high_resolution_clock::now();
		delta_time = chrono::duration_cast<chrono::duration<double>>(current_t - previous_t);
		if (alpha_increasing) {
			alpha += (float)(1 * REFRESH_SPEED * delta_time.count());
			alpha = min(1.f, alpha);
			if (alpha == 1.f) { alpha_increasing = false; };
		}
		else {
			alpha -= (float)(1 * REFRESH_SPEED * delta_time.count());
			alpha = max(0.f, alpha);
			if (alpha == 0.f) { alpha_increasing = true; };
		}
		previous_t = chrono::high_resolution_clock::now();

		// RENDER
		data_vertical_squares[0][3] = alpha;
		data_vertical_squares[5][3] = alpha;
		data_vertical_squares[10][3] = alpha;
		data_vertical_squares[15][3] = alpha;
		data_vertical_squares[20][3] = alpha;
		data_vertical_squares[25][3] = alpha;
		data_vertical_squares[30][3] = alpha;
		data_vertical_squares[35][3] = alpha;

		// Linear Transformation
		glTranslatef(-4., -4., -6.);

		glPushMatrix();

		DrawMultiplePoints(GL_QUADS, commands_horizontal_squares, data_horizontal_squares);

		DrawMultiplePoints(GL_QUADS, commands_vertical_squares, data_vertical_squares);

		glPopMatrix();


		// INPUT EVENT HANDLING
		while (SDL_PollEvent(&sdl_event)) {
			switch (sdl_event.type) {
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