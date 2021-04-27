#include "exercises.h"

const double MOVEMENT_CAMERA_SPEED = 0.005f;
const float MOUSE_SENSITIVITY = 0.1f;

// Reference: https://learnopengl.com/Getting-started/Camera

int pr3_ej1() {
	// DOCUMENTATION
	cout << "Controles:" << endl;
	cout << " ESC         -> Salir" << endl;
	cout << " FLECHAS     -> Mover Camara" << endl;

	// VARIABLES
	bool program_running = true;
	SDL_Event sdl_event;
	const Uint8* keyboard_state;

	color clear_color = BLACK;
	position camera_eye = { 0.f, 0.f, 1.f }; // Specifies the position of the eye point.
	position camera_front = { 0.f, 0.f, -1.f }; // Specifies the position of the reference point.
	position camera_up = { 0.f, 1.f, 0.f }; // Specifies the direction of the up vector.
	position normalized_front_up;

	chrono::duration<double> delta_time;
	chrono::high_resolution_clock::time_point current_t, previous_t;

	float camera_speed;
	float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
	float pitch = 0.0f;
	float mouse_offset_x, mouse_offset_y;

	// INITIALIZE WINDOW
	SDL_Window* window;
	SDL_GLContext context;
	tie(window, context) = InitializeSDL("Pr3-Ej1", SCR_WIDTH, SCR_HEIGHT);
	SDL_SetRelativeMouseMode(SDL_TRUE);

	glMatrixMode(GL_PROJECTION);
	glClearColor(clear_color.red, clear_color.green, clear_color.blue, clear_color.alpha);

	gluPerspective(45, SCR_WIDTH / (float)SCR_HEIGHT, 0.1, 100);

	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);

	// INTIALIZE DATA
	vector<char> commands_reference = { 'C', 'V', 'V', 'V', 'V', 'C', 'V', 'V', 'V', 'V', 'C', 'V', 'V' , 'V' , 'V' };
	vector<vector<float>> data_reference = {
		{1.f, 0.f, 0.f, 1.f},
		{-1.0f, -1.0f, 0.f}, {1.0f, -1.0f, 0.f}, {1.0f, 1.0f, 0.f}, {-1.0f, 1.0f, 0.f},
		{0.f, 1.f, 0.f, 1.f},
		{0.f, -1.0f, -1.0f}, {0.f, -1.0f, 1.0f}, {0.f, 1.0f, 1.0f}, {0.f, 1.0f, -1.0f},
		{0.f, 0.f, 1.f, 1.f},
		{-1.0f, 0.f, -1.0f}, {1.0f, 0.f, -1.0f}, {1.0f, 0.f, 1.0f}, {-1.0f, 0.f, 1.0f}
	};

	vector<char> commands_triangle_row = { 'V', 'V', 'V', 'V', 'V', 'V', 'V', 'V', 'V', 'V', 'V', 'V', 'V', 'V', 'V', 'V', 'V', 'V' };
	vector<vector<float>> data_triangle_row = {
		{0., 1., 0.}, {-1., -1., 0.}, {1., -1., 0.},
		{0., 3., 0.}, {-1., 1., 0.}, {1., 1., 0.},
		{0., 5., 0.}, {-1., 3., 0.}, {1., 3., 0.},
		{0., 7., 0.}, {-1., 5., 0.}, {1., 5., 0.},
		{0., 9., 0.}, {-1., 7., 0.}, {1., 7., 0.},
		{0., 11., 0.}, {-1., 9., 0.}, {1., 9., 0.}
	};

	vector<vector<float>> translate_triangle_rows = {
		{1., 0., 0.},
		{2., 0., 0.},
		{3., 0., 0.},
		{0., 0., 1.},
		{0., 0., 2.},
		{0., 0., 3.},
		{1., 0., 1.},
		{2., 0., 2.},
		{3., 0., 3.},
	};

	vector<vector<float>> color_triangle_rows = {
		{1., 1., 0.},
		{1., 0., 1.},
		{0., 1., 1.},
		{1., 0., 1.},
		{1., 0., 1.},
		{0., 1., 1.},
		{1., 0., 1.},
		{1., 0., 1.},
		{0., 1., 1.}
	};

	previous_t = chrono::high_resolution_clock::now();
	// RENDER LOOP
	do {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();

		current_t = chrono::high_resolution_clock::now();
		delta_time = chrono::duration_cast<chrono::duration<double>>(current_t - previous_t);
		// camera_eye.x = (float)sin(delta_time.count()) * 10.f; // Radius = 10.f
		// camera_eye.z = (float)cos(delta_time.count()) * 10.f; // Radius = 10.f 
		gluLookAt(
			camera_eye.x, camera_eye.y, camera_eye.z,
			camera_eye.x + camera_front.x, camera_eye.y + camera_front.y, camera_eye.z + camera_front.z,
			camera_up.x, camera_up.y, camera_up.z
		);
		
		camera_speed = (float)(MOVEMENT_CAMERA_SPEED * delta_time.count());

		// INPUT EVENT HANDLING
		keyboard_state = SDL_GetKeyboardState(NULL);
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
			case SDL_MOUSEMOTION:
				mouse_offset_x = MOUSE_SENSITIVITY * (sdl_event.motion.xrel);
				mouse_offset_y = MOUSE_SENSITIVITY * (-sdl_event.motion.yrel); // reversed since y-coordinates go from bottom to top

				yaw += mouse_offset_x;
				pitch += mouse_offset_y;

				// make sure that when pitch is out of bounds, screen doesn't get flipped
				if (pitch > 89.0f)
					pitch = 89.0f;
				if (pitch < -89.0f)
					pitch = -89.0f;

				camera_front = normalize_vector({
					cos(degree_to_radian(yaw)) * cos(degree_to_radian(pitch)),
					sin(degree_to_radian(pitch)),
					sin(degree_to_radian(yaw)) * cos(degree_to_radian(pitch))
				});
				break;
			}
			// Keys pressed
			if (keyboard_state[SDL_SCANCODE_UP] || keyboard_state[SDL_SCANCODE_W]) {
				camera_eye.x += camera_speed * camera_front.x;
				camera_eye.y += camera_speed * camera_front.y;
				camera_eye.z += camera_speed * camera_front.z;
			}
			if (keyboard_state[SDL_SCANCODE_RIGHT] || keyboard_state[SDL_SCANCODE_D]) {
				normalized_front_up = normalize_vector(cross_product_vector(camera_front, camera_up));
				camera_eye.x += camera_speed * normalized_front_up.x;
				camera_eye.y += camera_speed * normalized_front_up.y;
				camera_eye.z += camera_speed * normalized_front_up.z;
			}
			if (keyboard_state[SDL_SCANCODE_DOWN] || keyboard_state[SDL_SCANCODE_S]) {
				camera_eye.x -= camera_speed * camera_front.x;
				camera_eye.y -= camera_speed * camera_front.y;
				camera_eye.z -= camera_speed * camera_front.z;
			}
			if (keyboard_state[SDL_SCANCODE_LEFT] || keyboard_state[SDL_SCANCODE_A]) {
				normalized_front_up = normalize_vector(cross_product_vector(camera_front, camera_up));
				camera_eye.x -= camera_speed * normalized_front_up.x;
				camera_eye.y -= camera_speed * normalized_front_up.y;
				camera_eye.z -= camera_speed * normalized_front_up.z;
			}
		}

		// RENDER

		// Linear Transformation
		// glTranslatef(0., 0., 0.);

		glPushMatrix();

		DrawMultiplePoints(GL_QUADS, commands_reference, data_reference);

		// Ref: http://www.songho.ca/opengl/gl_displaylist.html
		// Create a display list
		GLuint display_list = glGenLists(1);

		// Compile the display list, store a triangle in it
		glNewList(display_list, GL_COMPILE);
			DrawMultiplePoints(GL_TRIANGLES, commands_triangle_row, data_triangle_row);
		glEndList();
		
		// Draw the display list N times
		for (size_t i = 0; i < translate_triangle_rows.size(); i++) {
			glPushMatrix();
			glTranslatef(translate_triangle_rows[i][0], translate_triangle_rows[i][1], translate_triangle_rows[i][2]);
			glColor3f(color_triangle_rows[i][0], color_triangle_rows[i][1], color_triangle_rows[i][2]);
			glCallList(display_list);
			glPopMatrix();
		}
		glPopMatrix();

		// Delete it if it is not used any more
		glDeleteLists(display_list, 1);

		
		SDL_GL_SwapWindow(window);
	} while (program_running);

	// CLEANUP
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}