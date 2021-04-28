#include "headers.h"

int game() {

	// DOCUMENTATION
	cout << "Controles:" << endl;
	cout << " FLECHAS/WASD -> Mover Camara" << endl;
	cout << " ESC          -> Salir" << endl;

	// VARIABLES
	bool program_running = true;
	SDL_Event sdl_event;
	const Uint8* keyboard_state;
	chrono::duration<double> delta_time;
	chrono::high_resolution_clock::time_point current_t, previous_t;

	color clear_color = { 0.3f, 0.3f, 0.3f, 1.f }; // RGBA
	position camera_eye = { 0.f, 0.f, 1.f }; // Specifies the position of the eye point.
	position camera_front = { 0.f, 0.f, -1.f }; // Specifies the position of the reference point.
	position camera_up = { 0.f, 1.f, 0.f }; // Specifies the direction of the up vector.

	float camera_speed;
	float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
	float pitch = 0.0f;
	float mouse_offset_x, mouse_offset_y;

	// INITIALIZE WINDOW
	SDL_Window* window;
	SDL_GLContext context;
	tie(window, context) = InitializeSDL("Pr2-Ej1", SCR_WIDTH, SCR_HEIGHT);
	SDL_SetRelativeMouseMode(SDL_TRUE);

	glMatrixMode(GL_PROJECTION);
	glClearColor(clear_color.red, clear_color.green, clear_color.blue, clear_color.alpha);

	gluPerspective(45, SCR_WIDTH / (float)SCR_HEIGHT, 0.1, 100);

	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);

	vector<char> commands_reference = { 'C', 'V', 'V', 'V', 'V', 'C', 'V', 'V', 'V', 'V', 'C', 'V', 'V' , 'V' , 'V' };
	vector<vector<float>> data_reference = {
		{1.f, 0.f, 0.f, 1.f},
		{-1.0f, -1.0f, 0.f}, {1.0f, -1.0f, 0.f}, {1.0f, 1.0f, 0.f}, {-1.0f, 1.0f, 0.f},
		{0.f, 1.f, 0.f, 1.f},
		{0.f, -1.0f, -1.0f}, {0.f, -1.0f, 1.0f}, {0.f, 1.0f, 1.0f}, {0.f, 1.0f, -1.0f},
		{0.f, 0.f, 1.f, 1.f},
		{-1.0f, 0.f, -1.0f}, {1.0f, 0.f, -1.0f}, {1.0f, 0.f, 1.0f}, {-1.0f, 0.f, 1.0f}
	};

	previous_t = chrono::high_resolution_clock::now();
	// RENDER LOOP
	do {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();

		current_t = chrono::high_resolution_clock::now();
		delta_time = chrono::duration_cast<chrono::duration<double>>(current_t - previous_t);
		gluLookAt(
			camera_eye.x, camera_eye.y, camera_eye.z,
			camera_eye.x + camera_front.x, camera_eye.y + camera_front.y, camera_eye.z + camera_front.z,
			camera_up.x, camera_up.y, camera_up.z
		);
		camera_speed = (float)(MOVEMENT_CAMERA_SPEED * delta_time.count());
		
		// RENDER
		glPushMatrix();

		DrawMultiplePoints(GL_QUADS, commands_reference, data_reference);

		glPopMatrix();

		// INPUT EVENT HANDLING
		keyboard_state = SDL_GetKeyboardState(NULL);
		FreeCamera::update_camera_eye(camera_speed, keyboard_state, camera_front, camera_up, camera_eye);
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
				case SDLK_F11:
					ToggleFullscreen(window);
					break;
				}
				break;
			case SDL_MOUSEMOTION:
				mouse_offset_x = MOUSE_SENSITIVITY * (sdl_event.motion.xrel);
				mouse_offset_y = MOUSE_SENSITIVITY * (-sdl_event.motion.yrel); // reversed since y-coordinates go from bottom to top
				camera_front = FreeCamera::update_camera_front(mouse_offset_x, mouse_offset_y, yaw, pitch);
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
