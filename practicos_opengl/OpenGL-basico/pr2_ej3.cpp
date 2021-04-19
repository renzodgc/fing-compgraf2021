#include "exercises.h"

const double ANGULAR_SPEED = 0.2; // Hz (1 turn / 5 seconds)
const string POLYGON_FILE = "../practicos/pr2/lightPolygons.txt";

int pr2_ej3() {
	// DOCUMENTATION
	cout << "Controles:" << endl;
	cout << " ESC         -> Salir" << endl;
	cout << " MOUSE CLICK -> Static/Translation Render" << endl;
	cout << " ESPACIO     -> Recargar datos" << endl;

	// VARIABLES
	bool program_running = true;
	SDL_Event sdl_event;
	square sq;

	color clear_color = BLACK;
	position camera_eye = { 0.f, 0.f, 0.5f }; // XYZ
	GLfloat light_position[4] = { 0, 0, 0, 1 };
	GLfloat light_color[4] = {1, 1, 1, 1};

	float rotation_angle = 0.f;
	chrono::duration<double> delta_time;
	chrono::high_resolution_clock::time_point current_t, previous_t;

	// INITIALIZE WINDOW
	SDL_Window* window;
	SDL_GLContext context;
	tie(window, context) = InitializeSDL("Pr2-Ej3", SCR_WIDTH, SCR_HEIGHT);

	glMatrixMode(GL_PROJECTION);
	glClearColor(clear_color.red, clear_color.green, clear_color.blue, clear_color.alpha);

	gluPerspective(45, SCR_WIDTH / (float)SCR_HEIGHT, 0.1, 100);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);

	// INTIALIZE DATA
	vector<char> commands;
	vector<vector<float>> data;
	tie(commands, data) = LoadTrianglePolygonFile(POLYGON_FILE);

	vector<char> commands_light = { 'C', 'V', 'V' , 'V' , 'V' , 'V', 'V' , 'V' , 'V' , 'V', 'V' , 'V' , 'V' };
	vector<vector<float>> data_light = {
		{1.f, 1.f, 1.f, 1.f},
		{-0.1f, -0.1f, 0.f}, {0.1f, -0.1f, 0.f}, {0.1f, 0.1f, 0.f}, {-0.1f, 0.1f, 0.f},
		{0.f, -0.1f, -0.1f}, {0.f, -0.1f, 0.1f}, {0.f, 0.1f, 0.1f}, {0.f, 0.1f, -0.1f},
		{-0.1f, 0.f, -0.1f}, {0.1f, 0.f, -0.1f}, {0.1f, 0.f, 0.1f}, {-0.1f, 0.f, 0.1f}
	};

	previous_t = chrono::high_resolution_clock::now();
	// RENDER LOOP
	do {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		gluLookAt(camera_eye.x, camera_eye.y, camera_eye.z, 0, 0, 0, 0, 1, 0);

		current_t = chrono::high_resolution_clock::now();
		delta_time = chrono::duration_cast<chrono::duration<double>>(current_t - previous_t);
		rotation_angle += (float)(360 * ANGULAR_SPEED * delta_time.count());
		previous_t = chrono::high_resolution_clock::now();

		// RENDER

		// Linear Transformation
		glTranslatef(0.0, 0.0, -6.);

		glPushMatrix();

		glRotatef(rotation_angle, 0.0f, 1.0f, 0.0f);

		glTranslatef(2.0, 1.0, 1.5);

		glDisable(GL_LIGHTING);

		DrawMultiplePoints(GL_QUADS, commands_light, data_light);

		glEnable(GL_LIGHTING);

		// Enable lighting (always after gluLookAt)
		glEnable(GL_LIGHT0); // enable light 0
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color);

		glPopMatrix();

		glRotatef(30.f, 0.0f, 1.0f, 0.0f);

		DrawMultiplePoints(GL_QUADS, commands, data);

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
				case SDLK_SPACE:
					for (size_t i = 0; i < data.size(); i++) { data[i].clear(); }
					data.clear();
					commands.clear();
					tie(commands, data) = LoadTrianglePolygonFile(POLYGON_FILE);
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

