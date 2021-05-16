#include "headers.h"

using namespace std;

int main(int argc, char* argv[]) {

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
	cout << " F3       -> Toggle Facetado/Interpolado" << endl; // Refiere al tipo de iluminacion, si liso o interpolado (flag de luz)
	cout << " Q/ESC    -> Salir" << endl;

	// INITIALIZE WINDOW
	SDL_Window* window;
	SDL_GLContext context;
	tie(window, context) = InitializeSDL("Game", SCR_WIDTH, SCR_HEIGHT);

	// FLAGS
	bool program_running = true;
	bool paused = false;
	bool wireframe = false;
	bool textures = true;
	bool interpolated_lightning = false;

	// GENERAL OBJECTS AND VARIABLES
	SDL_Event sdl_event;
	const Uint8* keyboard_state;
	float mouse_offset_x, mouse_offset_y;
	chrono::duration<double> delta_time;
	double elapsed_time;
	chrono::high_resolution_clock::time_point current_t, previous_t;

	// MAIN OBJECTS
	Player& player = Player::get_instance();

	// MANAGERS
	Game& game_manager = Game::get_instance();
	Draw& draw_manager = Draw::get_instance();
	UI& ui = UI::get_instance();
	Camera& camera = Camera::get_instance();

	// RENDER LOOP
	camera.start_third_person_view();
	current_t = chrono::high_resolution_clock::now();
	do {

		// PRE RENDER
		// -----------------------------------------------------------------------------------------------

		// If Paused: Check if P, Q or ESC are pressed, skip rest of the loop
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();

		// TIME CALCULATIONS
		// -----------------------------------------------------------------------------------------------
		
		previous_t = current_t;
		current_t = chrono::high_resolution_clock::now();
		delta_time = chrono::duration_cast<chrono::duration<double>>(current_t - previous_t);
		elapsed_time = delta_time.count();

		// INPUT EVENT HANDLING
		// -----------------------------------------------------------------------------------------------
		
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
					game_manager.update(player.get_player_position().z);
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

		// UPDATE
		// -----------------------------------------------------------------------------------------------
		
		// Update player
		player.update(elapsed_time);

		// Update lanes
		for (size_t i = 0; i < game_manager.getLanes().size(); i++) {
			game_manager.getLanes()[i]->update(elapsed_time);
		}

		// Update camera
		camera.update_position(elapsed_time, keyboard_state);
		camera.call_look_at();

		// Update HUD
		if (game_manager.getScore() < -player.get_player_position().z) {
			game_manager.setScore((int)-player.get_player_position().z);
			ui.set_score(game_manager.getScore());
		}

		// RENDER
		// -----------------------------------------------------------------------------------------------

		glPushMatrix();
		
		// Draw origin reference
		draw_manager.DrawReferenceObject();

		// Draw "floor" as reference
		draw_manager.DrawMultiplePoints(GL_QUADS, { 'C', 'V', 'V', 'V', 'V' }, {
			{0.7f, 0.7f, 0.7f, 1.f},
			{-500.f, -1.f, -500.f},
			{-500.f, -1.f, 500.f},
			{500.f, -1.f, 500.f},
			{500.f, -1.f, -500.f}
		});

		// Draw player
		player.draw(textures);

		// Draw lanes
		for (size_t i = 0; i < game_manager.getLanes().size(); i++) {
			game_manager.getLanes()[i]->draw(textures);
		}

		// Draw HUD
		ui.draw();
		
		glPopMatrix();

		// POST RENDER
		// -----------------------------------------------------------------------------------------------
		SDL_GL_SwapWindow(window);

	} while (program_running);

	// FINAL CLEANUP
	ui.clean_memory();
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();

	return 0;
}
