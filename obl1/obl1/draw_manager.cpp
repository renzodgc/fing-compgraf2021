// HEADERS
// -----------------------------------------------------------------------------------
#include "draw_manager.h"

// NAMESPACE
// -----------------------------------------------------------------------------------
using namespace std;

// METHODS
// -----------------------------------------------------------------------------------

void DrawTexturedSquare(GLuint texture, textured_square square) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUADS);
	glColor3f(square.color.red, square.color.green, square.color.blue);
	glTexCoord2f(square.tex_a.x, square.tex_a.y); glVertex3f(square.a.x, square.a.y, square.a.z);
	glTexCoord2f(square.tex_b.x, square.tex_b.y); glVertex3f(square.b.x, square.b.y, square.b.z);
	glTexCoord2f(square.tex_c.x, square.tex_c.y); glVertex3f(square.c.x, square.c.y, square.c.z);
	glTexCoord2f(square.tex_d.x, square.tex_d.y); glVertex3f(square.d.x, square.d.y, square.d.z);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void DrawCube() {
	DrawMultiplePoints(GL_QUADS, COMMANDS_CUBE_OBJECT, DATA_CUBE_OBJECT);
}

void DrawReferenceObject() {
	DrawMultiplePoints(GL_QUADS, COMMANDS_REFERENCE_OBJECT, DATA_REFERENCE_OBJECT);
}

void DrawHUD(HUDComponent left, HUDComponent right) {
	int height = max(left.height, right.height);
	DrawHUDComponent(left);
	DrawHUDComponent(right);

	// Draw the rest of the overlay
	glBegin(GL_QUADS); {
		glColor3f(0.f, 0.f, 0.f);
		glVertex3f(0.f, height + 6.f, 0.f);
		glVertex3f(SCR_WIDTH, height + 6.f, 0.f);
		glVertex3f(SCR_WIDTH, 0.f, 0.f);
		glVertex3f(0.f, 0.f, 0.f);
	} glEnd();
}

void DrawHUDComponent(HUDComponent component) {
	glEnable(GL_TEXTURE_2D);
	SDL_BlitSurface(component.surface_message, NULL, component.rgb_surface, NULL);

	//Avoid mipmap filtering
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	//Copy the created image into OpenGL format
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, component.width, component.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, component.rgb_surface->pixels);

	switch (component.position) {
	case HUDComponentIs::left:
		glBegin(GL_QUADS); {
			glTexCoord2d(0.f, 1.f); glVertex3f(30.f, 3.f + component.surface_message->h, 0.f);
			glTexCoord2d(1.f, 1.f); glVertex3f(30.f + component.surface_message->w, 3.f + component.surface_message->h, 0.f);
			glTexCoord2d(1.f, 0.f); glVertex3f(30.f + component.surface_message->w, 3.f, 0.f);
			glTexCoord2d(0.f, 0.f); glVertex3f(30.f, 3.f, 0.f);
		} glEnd();
		break;
	case HUDComponentIs::right:
		glBegin(GL_QUADS); {
			glTexCoord2d(0.f, 1.f); glVertex3f(SCR_WIDTH - 30.f - component.surface_message->w, 3.f + component.surface_message->h, 0.f);
			glTexCoord2d(1.f, 1.f); glVertex3f(SCR_WIDTH - 30.f, 3.f + component.surface_message->h, 0.f);
			glTexCoord2d(1.f, 0.f); glVertex3f(SCR_WIDTH - 30.f, 3.f, 0.f);
			glTexCoord2d(0.f, 0.f); glVertex3f(SCR_WIDTH - 30.f - component.surface_message->w, 3.f, 0.f);
		} glEnd();
		break;
	}
	glDisable(GL_TEXTURE_2D);
}

void DrawLane(LaneIs laneType) {
	switch (laneType) {
	case LaneIs::grass:
		DrawMultiplePoints(GL_QUADS, COMMANDS_LANE_OBJECT, DATA_LANE_GRASS_OBJECT);
		break;
	case LaneIs::street:
		DrawMultiplePoints(GL_QUADS, COMMANDS_LANE_OBJECT, DATA_LANE_STREET_OBJECT);
		break;
	default:
		break;
	}
	
}

void DrawMultiplePoints(GLenum primitive, vector<char> commands, vector<vector<float>> data) {
	glBegin(primitive);
	for (size_t i = 0; i < commands.size(); i++) {
		switch (commands[i]) {
		case('C'): {
			glColor3f(data[i][0], data[i][1], data[i][2]);
			break;
		}
		case('V'): {
			glVertex3f(data[i][0], data[i][1], data[i][2]);
			break;
		}
		case('N'): {
			glNormal3f(data[i][0], data[i][1], data[i][2]);
			break;
		}
		case('A'): {
			glColor4f(data[i][0], data[i][1], data[i][2], data[i][3]);
			break;
		}
		}
	}
	glEnd();
}
