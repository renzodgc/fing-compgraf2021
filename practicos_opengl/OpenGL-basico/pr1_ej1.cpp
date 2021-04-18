#include "exercises.h"


#define SDL_NUMERIC_MINUS 1073741910
#define SDL_NUMERIC_PLUS 1073741911

int pr1_ej1() {
	// DOCUMENTATION
	cout << "Controles:" << endl;
	cout << "   R -> Incrementar Rojo" << endl;
	cout << "   G -> Incrementar Verde" << endl;
	cout << "   B -> Incrementar Azul" << endl;
	cout << "   + -> Incrementar Blanco" << endl;
	cout << "   - -> Decrementar Blanco" << endl;
	cout << " ESC -> Salir" << endl;

	// VARIABLES
	bool program_running = true;
	SDL_Event sdl_event;

	color clear_color = { 0.3f, 0.3f, 0.3f, 1.f }; // RGBA

	// INITIALIZE WINDOW
	SDL_Window* window;
	SDL_GLContext context;
	tie(window, context) = InitializeSDL("Pr2-Ej1", SCR_WIDTH, SCR_HEIGHT);

	glMatrixMode(GL_PROJECTION);
	glClearColor(clear_color.red, clear_color.green, clear_color.blue, clear_color.alpha);

	// RENDER LOOP
	do {
		glClearColor(clear_color.red, clear_color.green, clear_color.blue, clear_color.alpha);
		glClear(GL_COLOR_BUFFER_BIT);

		// RENDER
		

		// INPUT EVENT HANDLING
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
				case SDLK_r:
					clear_color.red = min(clear_color.red + 0.1f, 1.0f);
					break;
				case SDLK_g:
					clear_color.green = min(clear_color.green + 0.1f, 1.0f);
					break;
				case SDLK_b:
					clear_color.blue = min(clear_color.blue + 0.1f, 1.0f);
					break;
				case SDLK_PLUS:
				case SDL_NUMERIC_PLUS:
					clear_color.red = min(clear_color.red + 0.1f, 1.0f);
					clear_color.green = min(clear_color.green + 0.1f, 1.0f);
					clear_color.blue = min(clear_color.blue + 0.1f, 1.0f);
					break;
				case SDLK_MINUS:
				case SDL_NUMERIC_MINUS:
					clear_color.red = max(clear_color.red - 0.1f, 0.0f);
					clear_color.green = max(clear_color.green - 0.1f, 0.0f);
					clear_color.blue = max(clear_color.blue - 0.1f, 0.0f);
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
