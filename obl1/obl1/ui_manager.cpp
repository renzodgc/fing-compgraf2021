// HEADERS
// -----------------------------------------------------------------------------------
#include "ui_manager.h"

// NAMESPACE
// -----------------------------------------------------------------------------------
using namespace std;

// METHODS
// -----------------------------------------------------------------------------------

// Reference: https://stackoverflow.com/questions/30016083/sdl2-opengl-sdl2-ttf-displaying-text
UI::UI() {
	draw_manager = &Draw::get_instance();
	
	font = TTF_OpenFont("OpenSans-Regular.ttf", 24); //this opens a font style and sets a size
	if (font == nullptr) {
		cerr << "TTF_OpenFont error: " << SDL_GetError() << endl;
		return;
	}
	score.message_color = { 255, 255, 255 };
	coins.message_color = { 255, 255, 0 };

	score.position = HUDComponentIs::left;
	coins.position = HUDComponentIs::right;

	set_score(0);
	set_coins(0);
}

UI& UI::get_instance() {
	static UI instance; // Guaranteed to be destroyed. Instantiated on first use.
	return instance;
}

void UI::clean_memory() {
	SDL_FreeSurface(score.surface_message);
	SDL_FreeSurface(score.rgb_surface);
	SDL_FreeSurface(coins.surface_message);
	SDL_FreeSurface(coins.rgb_surface);
	TTF_CloseFont(font);
}


void UI::draw() {
	glMatrixMode(GL_PROJECTION); glPushMatrix(); glLoadIdentity();
	glOrtho(0, SCR_WIDTH, SCR_HEIGHT, 0, -1.0, 1.0);

	glMatrixMode(GL_MODELVIEW); glPushMatrix(); glLoadIdentity();

	draw_manager->DrawHUD(score, coins);

	glMatrixMode(GL_PROJECTION); glPopMatrix();
	glMatrixMode(GL_MODELVIEW); glPopMatrix();
}

void UI::set_score(int score_number) {
	string message = "Score: " + to_string(score_number);
	set_message_on_component(message, &score);
}

void UI::set_coins(int coins_number) {
	string message = "Coins: " + to_string(coins_number);
	set_message_on_component(message, &coins);
}

void UI::set_message_on_component(string message, HUDComponent* component) {
	glColor3f(component->message_color.r, component->message_color.g, component->message_color.b);
	component->surface_message = TTF_RenderText_Blended(font, message.c_str(), {255, 255, 255});
	if (component->surface_message == NULL) {
		cerr << "TTF_RenderText error: " << SDL_GetError() << endl;
		return;
	}

	//Generate OpenGL texture
	glEnable(GL_TEXTURE_2D);
		glGenTextures(1, &(component->texture_id));
		glBindTexture(GL_TEXTURE_2D, component->texture_id);
	
		TTF_SizeText(font, message.c_str(), &(component->width), &(component->height));
	
		//Create a surface to the correct size in RGB format, and copy the old image
		component->rgb_surface = SDL_CreateRGBSurface(0, component->width, component->height, 32, 0, 0x0000ff00, 0x000000ff, 0xff000000);
		if (component->rgb_surface == NULL) {
			cerr << "SDL_CreateRGBSurface() failed: " << SDL_GetError() << endl;
			exit(1);
		}
		SDL_BlitSurface(component->surface_message, NULL, component->rgb_surface, NULL);

		//Avoid mipmap filtering
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		//Copy the created image into OpenGL format
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, component->width, component->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, component->rgb_surface->pixels);
		glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
}
