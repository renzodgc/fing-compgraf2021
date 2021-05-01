// HEADERS
// -----------------------------------------------------------------------------------
#include "draw_helper.h"

// NAMESPACE
// -----------------------------------------------------------------------------------
using namespace std;

// METHODS
// -----------------------------------------------------------------------------------

void DrawTriangle(triangle triangle) {
	glBegin(GL_TRIANGLES);
	glColor3f(triangle.color.red, triangle.color.green, triangle.color.blue);
	glVertex3f(triangle.a.x, triangle.a.y, triangle.a.z);
	glVertex3f(triangle.b.x, triangle.b.y, triangle.b.z);
	glVertex3f(triangle.c.x, triangle.c.y, triangle.c.z);
	glEnd();
}

void DrawMulticoloredTriangle(multicolored_triangle triangle) {
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < 3; i++) {
		glColor3f(triangle.color_a.red, triangle.color_a.green, triangle.color_a.blue);
		glVertex3f(triangle.a.x, triangle.a.y, triangle.a.z);
		glColor3f(triangle.color_b.red, triangle.color_b.green, triangle.color_b.blue);
		glVertex3f(triangle.b.x, triangle.b.y, triangle.b.z);
		glColor3f(triangle.color_c.red, triangle.color_c.green, triangle.color_c.blue);
		glVertex3f(triangle.c.x, triangle.c.y, triangle.c.z);
	}
	glEnd();
}

void DrawSquare(square square) {
	glBegin(GL_QUADS);
	glColor3f(square.color.red, square.color.green, square.color.blue);
	glVertex3f(square.a.x, square.a.y, square.a.z);
	glVertex3f(square.b.x, square.b.y, square.b.z);
	glVertex3f(square.c.x, square.c.y, square.c.z);
	glVertex3f(square.d.x, square.d.y, square.d.z);
	glEnd();
}

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

void DrawCube() {
	DrawMultiplePoints(GL_QUADS, COMMANDS_CUBE_OBJECT, DATA_CUBE_OBJECT);
}

void DrawReferenceObject() {
	DrawMultiplePoints(GL_QUADS, COMMANDS_REFERENCE_OBJECT, DATA_REFERENCE_OBJECT);
}
