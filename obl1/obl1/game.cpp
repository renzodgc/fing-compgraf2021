#include "headers.h"

double MOVEMENT_RATE = 0.5;

int game() {

	// DOCUMENTATION
	cout << "Controles:" << endl;
	cout << " FLECHAS  -> Mover Personaje" << endl;
	cout << " WASD     -> Mover Camara" << endl;
	cout << " MOUSE    -> Rotar Camara" << endl;
	cout << " I        -> Vista Isometrica" << endl;
	cout << " T        -> Vista Tercera Persona" << endl;
	cout << " F        -> Vista Libre" << endl;
	cout << " P        -> Pausa" << endl;
	cout << " F11      -> Pantalla Completa" << endl;
	cout << " F1       -> Toggle Wireframe On/Off" << endl;
	cout << " F2       -> Toggle Texturas On/Off" << endl;
	cout << " F3       -> Toggle Facetado/Interpolado" << endl; // Refiere al tipo de iluminación, si liso o interpolado (flag de luz)
	cout << " Q/ESC    -> Salir" << endl;

	// VARIABLES
	bool program_running = true;
	bool paused = false;
	bool wireframe = false;
	bool textures = false;
	bool interpolated_lightning = false;
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
	camera.start_third_person_view();
	current_t = chrono::high_resolution_clock::now();
	do {
		// If Paused: Check if P, Q or ESC are pressed, skip rest of the loop

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
				case SDLK_q:
					program_running = false;
					break;
				case SDLK_p:
					paused = !paused;
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
				case SDLK_F1:
					wireframe = !wireframe;
					if (wireframe)
						glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
					else
						glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
					break;
				case SDLK_F2:
					textures = !textures;
					break;
				case SDLK_F3:
					interpolated_lightning = !interpolated_lightning;
					break;
				case SDLK_F11:
					ToggleFullscreen(window);
					break;
				case SDLK_LEFT:
					player.move_left();
					break;
				case SDLK_RIGHT:
					player.move_right();
					break;
				case SDLK_UP:
					player.move_up();
					break;
				case SDLK_DOWN:
					player.move_down();
					break;
				}
				break;
			case SDL_MOUSEMOTION:
				mouse_offset_x = MOUSE_SENSITIVITY * (sdl_event.motion.xrel);
				mouse_offset_y = MOUSE_SENSITIVITY * (-sdl_event.motion.yrel); // reversed since y-coordinates go from bottom to top
				camera.update_angle(mouse_offset_x, mouse_offset_y);
				break;
			case SDL_MOUSEWHEEL:
				camera.update_distance(elapsed_time, sdl_event.wheel.y);
				break;
			}
		}
		keyboard_state = SDL_GetKeyboardState(NULL);

		// UPDATE OBJECTS

		// Player.update(action)
		/*if(player_moving) {
			player_position = player.get_player_position();
			player_position.x += (float)(MOVEMENT_RATE * elapsed_time);
			player.set_player_position(player_position);
		}*/
		player.update(elapsed_time);

		camera.update_position(elapsed_time, keyboard_state);

		// destroy old lanes, create new ones
		// for lane in lanes: update()

		camera.call_look_at();

		// RENDER
		glPushMatrix();

		DrawReferenceObject();

		// Draw "floor" as reference
		DrawMultiplePoints(GL_QUADS, { 'C', 'V', 'V', 'V', 'V' }, {
			{0.7f, 0.7f, 0.7f, 1.f},
			{-500.f, -1.f, -500.f},
			{-500.f, -1.f, 500.f},
			{500.f, -1.f, 500.f},
			{500.f, -1.f, -500.f}
		});

		// Draw player
		player.draw();

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
