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
	cout << " F3       -> Toggle Facetado/Interpolado" << endl;
	cout << " F4       -> Toggle Iluminacion (dia/tarde/noche)" << endl;
	cout << " F5       -> Toggle Velocidad (lento/normal/rapido)" << endl;
	cout << " Q/ESC    -> Salir" << endl;

	// INITIALIZE WINDOW
	SDL_Window* window;
	SDL_GLContext context;
	tie(window, context) = InitializeSDL("Game", SCR_WIDTH, SCR_HEIGHT);

	// FLAGS
	bool program_running = true;
	bool paused = false;
	bool game_over = false;
	bool wireframe = false;
	bool use_textures = true;
	bool interpolated_lightning = false; // Refiere al tipo de iluminacion, si liso o interpolado (flag de luz)
	LightningType lightning_type = LightningType::day;
	GameSpeed game_speed = GameSpeed::normal;
	double game_speed_multiplier = 1.f;

	// GENERAL OBJECTS AND VARIABLES
	SDL_Event sdl_event;
	const Uint8* keyboard_state;
	float mouse_offset_x, mouse_offset_y;
	chrono::duration<double> delta_time;
	double elapsed_time;
	chrono::high_resolution_clock::time_point current_t, previous_t;
	vector<OnCollision> collision_events;

	// Lightning
	GLfloat light_position[4] = { 0, 0, 0, 1 };
	GLfloat light_color[4] = { 1, 1, 1, 1 };
	GLfloat material_ambient_diffuse_color[4] = { 1, 1, 1, 1 };
	GLfloat material_specular_color[4] = { 0, 0, 0, 1 };

	// MAIN OBJECTS
	Player& player = Player::get_instance();

	// MANAGERS
	Game& game_manager = Game::get_instance();
	Draw& draw_manager = Draw::get_instance();
	UI& ui = UI::get_instance();
	Camera& camera = Camera::get_instance();
	FrustumGeometric& frustum = FrustumGeometric::get_instance();

	// CONFIG
	//glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, material_ambient_diffuse_color);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_specular_color);

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
		elapsed_time = delta_time.count() * game_speed_multiplier;
		if (LOG_FPS) {
			cout << (1.f / elapsed_time) << " FPS" << endl;
		}

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
					use_textures = !use_textures;
					break;
				case SDLK_F3:
					interpolated_lightning = !interpolated_lightning;
					if (interpolated_lightning)
						glShadeModel(GL_SMOOTH);
					else
						glShadeModel(GL_FLAT);
					break;
				case SDLK_F4:
					lightning_type = static_cast<LightningType>((((int)lightning_type + 1) % LIGHTNING_TYPES));
					switch (lightning_type) {
					case LightningType::day:
						light_color[0] = 0.8f; light_color[1] = 0.8f; light_color[2] = 0.2f;
						break;
					case LightningType::sunset:
						light_color[0] = 0.8f; light_color[1] = 0.4f; light_color[2] = 0.2f;
						break;
					case LightningType::night:
						light_color[0] = 0.f; light_color[1] = 0.2f; light_color[2] = 0.5f;
						break;
					}
					break;
				case SDLK_F5:
					game_speed = static_cast<GameSpeed>((((int)game_speed + 1) % GAMESPEED_TYPES));
					switch (game_speed) {
					case GameSpeed::slow:
						game_speed_multiplier = 0.5f;
						break;
					case GameSpeed::normal:
						game_speed_multiplier = 1.f;
						break;
					case GameSpeed::fast:
						game_speed_multiplier = 2.f;
						break;
					}
					break;
				case SDLK_F11:
					ToggleFullscreen(window);
					break;
				case SDLK_LEFT:
					if (!paused && !game_over) player.move_left();
					break;
				case SDLK_RIGHT:
					if (!paused && !game_over) player.move_right();
					break;
				case SDLK_UP:
					if (!paused && !game_over) {
						player.move_up();
						game_manager.update(player.get_player_position().z);
					}
					break;
				case SDLK_DOWN:
					if (!paused && !game_over) player.move_down();
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

		// Update camera
		camera.update_position(elapsed_time, keyboard_state);
		camera.call_look_at();

		if (!paused && !game_over) {

			// Update lanes
			for (size_t i = 0; i < game_manager.getLanes().size(); i++) {
				
				collision_events = game_manager.getLanes()[i]->update(elapsed_time, player.get_player_position());
				
				// Apply collisions events if any
				for (size_t i = 0; i < collision_events.size(); i++) {
					switch (collision_events[i]) {
					case OnCollision::bounce:
						player.bounce_back();
						break;
					case OnCollision::coin:
						game_manager.addCoin();
						ui.set_coins(game_manager.getCoins());
						break;
					case OnCollision::death:
						if (!IMMORTAL) {
							game_over = true;
						}
						ui.set_game_over(true);
						break;
					}
				}
			}

			// Update player
			player.update(elapsed_time);

			// Update HUD
			if (game_manager.getScore() < -player.get_player_position().z) {
				game_manager.setScore((int)-player.get_player_position().z);
				ui.set_score(game_manager.getScore());
			}

		}

		// RENDER
		// -----------------------------------------------------------------------------------------------

		glPushMatrix();

		// LIGHTNING
		if (use_textures) { // Else use flat coloring
			glEnable(GL_LIGHTING);
			// Enable lighting (always after gluLookAt)
			glEnable(GL_LIGHT0); // enable light 0
			light_position[0] = (GLfloat)(player.get_player_position().x + 0.2f);
			light_position[1] = (GLfloat)(player.get_player_position().y + 3.f);
			light_position[2] = (GLfloat)(player.get_player_position().z - 0.8f);
			glLightfv(GL_LIGHT0, GL_POSITION, light_position);
			glLightfv(GL_LIGHT0, GL_AMBIENT, light_color);
		}
		

		// Draw player
		player.draw(use_textures);

		// Draw lanes
		for (size_t i = 0; i < game_manager.getLanes().size(); i++) {
			game_manager.getLanes()[i]->draw(use_textures);
		}

		// Draw HUD
		glDisable(GL_LIGHTING);
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
