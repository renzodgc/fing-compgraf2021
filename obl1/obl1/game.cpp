#include "headers.h"

double MOVEMENT_RATE = 0.5;

int game() {

	// DOCUMENTATION
	cout << "Controles:" << endl;
	cout << " FLECHAS/WASD -> Mover Camara" << endl;
	cout << " ESC          -> Salir" << endl;

	// VARIABLES
	bool program_running = true;
	// We need an enum or something of what actions the player can take (and were taken) in order to pass them to update_player
	bool player_moving = true;

	SDL_Event sdl_event;
	const Uint8* keyboard_state;
	chrono::duration<double> delta_time;
	double elapsed_time;
	chrono::high_resolution_clock::time_point current_t, previous_t;

	position player_position;
	Player player = Player({ 3.f, 0.f, 3.f });
	Camera camera = Camera(&player);
	float mouse_offset_x, mouse_offset_y;

	// INITIALIZE WINDOW
	SDL_Window* window;
	SDL_GLContext context;
	tie(window, context) = InitializeSDL("Game", SCR_WIDTH, SCR_HEIGHT);

	// RENDER LOOP
	camera.start_isometric_view();
	current_t = chrono::high_resolution_clock::now();
	do {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();

		// INPUT EVENT HANDLING
		previous_t = current_t;
		current_t = chrono::high_resolution_clock::now();
		delta_time = chrono::duration_cast<chrono::duration<double>>(current_t - previous_t);
		elapsed_time = delta_time.count();

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
				case SDLK_p:
					player_moving = !player_moving;
					break;
				case SDLK_i:
					camera.start_isometric_view();
					break;
				case SDLK_t:
					camera.start_third_person_view();
					break;
				case SDLK_f:
					camera.start_free_view();
					break;
				}
				break;
			case SDL_MOUSEMOTION:
				mouse_offset_x = MOUSE_SENSITIVITY * (sdl_event.motion.xrel);
				mouse_offset_y = MOUSE_SENSITIVITY * (-sdl_event.motion.yrel); // reversed since y-coordinates go from bottom to top
				camera.update_angle(mouse_offset_x, mouse_offset_y);
				break;
			}
		}
		keyboard_state = SDL_GetKeyboardState(NULL);

		// UPDATE OBJECTS

		// Player.update(action)
		if(player_moving) {
			player_position = player.get_player_position();
			player_position.x += (float)(MOVEMENT_RATE * elapsed_time);
			player.set_player_position(player_position);
		}

		camera.update_position(elapsed_time, keyboard_state);

		// destroy old lanes, create new ones
		// for lane in lanes: update()

		camera.call_look_at();

		// RENDER
		glPushMatrix();

		DrawReferenceObject();

		player_position = player.get_player_position();
		glTranslatef(player_position.x, player_position.y, player_position.z);

		DrawCube();

		glPopMatrix();

		// RENDER CLEANUP
		SDL_GL_SwapWindow(window);
	} while (program_running);

	// CLEANUP
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
