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
