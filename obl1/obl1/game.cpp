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
	CameraType selected_camera = CameraType::free_view;

	camera current_camera;
	position player_position = { 3.f, 0.f, 3.f };

	float camera_speed;
	float mouse_offset_x, mouse_offset_y;

	// INITIALIZE WINDOW
	SDL_Window* window;
	SDL_GLContext context;
	tie(window, context) = InitializeSDL("Game", SCR_WIDTH, SCR_HEIGHT);
	SDL_SetRelativeMouseMode(SDL_TRUE);

	

	

	switch (selected_camera) {
	case CameraType::isometric:
		IsometricCamera::start_isometric_view(player_position, current_camera);
		break;
	case CameraType::third_person:
		ThirdPersonCamera::start_third_person_view(player_position, current_camera);
		break;
	case CameraType::free_view:
		FreeViewCamera::start_free_view(player_position, current_camera);
		break;
	}
	
	previous_t = chrono::high_resolution_clock::now();
	// RENDER LOOP
	do {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glLoadIdentity();

		current_t = chrono::high_resolution_clock::now();
		delta_time = chrono::duration_cast<chrono::duration<double>>(current_t - previous_t);

		switch (selected_camera) {
		case CameraType::isometric:
			gluLookAt(
				current_camera.camera_eye.x, current_camera.camera_eye.y, current_camera.camera_eye.z,
				current_camera.camera_front.x, current_camera.camera_front.y, current_camera.camera_front.z,
				current_camera.camera_up.x, current_camera.camera_up.y, current_camera.camera_up.z
			);
			break;
		case CameraType::third_person:
		case CameraType::free_view:
			gluLookAt(
				current_camera.camera_eye.x, current_camera.camera_eye.y, current_camera.camera_eye.z,
				current_camera.camera_eye.x + current_camera.camera_front.x, current_camera.camera_eye.y + current_camera.camera_front.y, current_camera.camera_eye.z + current_camera.camera_front.z,
				current_camera.camera_up.x, current_camera.camera_up.y, current_camera.camera_up.z
			);
			break;
		}

		
		camera_speed = (float)(MOVEMENT_CAMERA_SPEED * delta_time.count());
		
		// RENDER
		glPushMatrix();

		DrawReferenceObject();

		glTranslatef(player_position.x, player_position.y, player_position.z);

		DrawCube();

		glPopMatrix();

		// INPUT EVENT HANDLING
		keyboard_state = SDL_GetKeyboardState(NULL);
		if (selected_camera == CameraType::free_view || selected_camera == CameraType::third_person) {
			FreeViewCamera::update_camera_eye(camera_speed, keyboard_state, current_camera);
		}
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
				case SDLK_v:
					IsometricCamera::start_isometric_view(player_position, current_camera);
					selected_camera = CameraType::isometric;
					break;
				case SDLK_b:
					ThirdPersonCamera::start_third_person_view(player_position, current_camera);
					selected_camera = CameraType::third_person;
					break;
				case SDLK_n:
					FreeViewCamera::start_free_view(player_position, current_camera);
					selected_camera = CameraType::free_view;
					break;
				}
				break;
			case SDL_MOUSEMOTION:
				mouse_offset_x = MOUSE_SENSITIVITY * (sdl_event.motion.xrel);
				mouse_offset_y = MOUSE_SENSITIVITY * (-sdl_event.motion.yrel); // reversed since y-coordinates go from bottom to top
				if (selected_camera == CameraType::free_view || selected_camera == CameraType::third_person) {
					FreeViewCamera::update_camera_front(mouse_offset_x, mouse_offset_y, current_camera);
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
