// HEADERS
// -----------------------------------------------------------------------------------
#include "window_helper.h"

// NAMESPACE
// -----------------------------------------------------------------------------------
using namespace std;

// METHODS
// -----------------------------------------------------------------------------------

tuple<SDL_Window*, SDL_GLContext> InitializeSDL(string program_name, int scr_width, int scr_height) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cerr << "[Error]: No se pudo iniciar SDL: " << SDL_GetError() << endl;
		exit(1);
	}
	SDL_Window* window = SDL_CreateWindow(
		program_name.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		scr_width, scr_height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
	);
	if (window == NULL) {
		cerr << "[Video Error]: " << SDL_GetError() << endl;
		SDL_Quit();
		exit(1);
	}
	SDL_GLContext context = SDL_GL_CreateContext(window);
	if (context == NULL) {
		cerr << "[GL Context Error]: " << SDL_GetError() << endl;
		SDL_Quit();
		exit(1);
	}
	SDL_SetRelativeMouseMode(SDL_TRUE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	int ttf = TTF_Init();
	if (ttf == -1) {
		cerr << "[SDL TTF Error]: " << SDL_GetError() << endl;
		SDL_Quit();
		exit(1);
	}
	return { window, context };
}

void ToggleFullscreen(SDL_Window* Window) {
	Uint32 FullscreenFlag = SDL_WINDOW_FULLSCREEN;
	bool IsFullscreen = SDL_GetWindowFlags(Window)& FullscreenFlag;
	SDL_SetWindowFullscreen(Window, IsFullscreen ? 0 : FullscreenFlag);
	SDL_ShowCursor(IsFullscreen);
}
