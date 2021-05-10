// HEADERS
// -----------------------------------------------------------------------------------
#include "draw_manager.h"

// NAMESPACE
// -----------------------------------------------------------------------------------
using namespace std;

// METHODS
// -----------------------------------------------------------------------------------

Draw& Draw::get_instance() {
	static Draw instance; // Guaranteed to be destroyed. Instantiated on first use.
	return instance;
}

void Draw::DrawTexturedSquare(GLuint texture, textured_square square) {
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

void Draw::DrawCube() {
	Draw::DrawMultiplePoints(GL_QUADS, COMMANDS_CUBE_OBJECT, DATA_CUBE_OBJECT, NULL, false);
}

void Draw::DrawReferenceObject() {
	Draw::DrawMultiplePoints(GL_QUADS, COMMANDS_REFERENCE_OBJECT, DATA_REFERENCE_OBJECT, NULL, false);
}

void Draw::DrawHUD(HUDComponent left, HUDComponent right) {
	glPushMatrix();
	int height = max(left.height, right.height);
	Draw::DrawHUDComponent(left);
	Draw::DrawHUDComponent(right);

	// Draw the rest of the overlay
	glBegin(GL_QUADS); {
		glColor3f(0.f, 0.f, 0.f);
		glVertex3f(0.f, height + 6.f, 0.f);
		glVertex3f(SCR_WIDTH, height + 6.f, 0.f);
		glVertex3f(SCR_WIDTH, 0.f, 0.f);
		glVertex3f(0.f, 0.f, 0.f);
	} glEnd();
	glPopMatrix();
}

void Draw::DrawHUDComponent(HUDComponent component) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, component.texture_id);
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

void Draw::DrawLane(LaneIs laneType) {
	switch (laneType) {
	case LaneIs::grass:
		Draw::DrawMultiplePoints(GL_QUADS, COMMANDS_LANE_OBJECT, DATA_LANE_GRASS_OBJECT);
		break;
	case LaneIs::street:
		Draw::DrawMultiplePoints(GL_QUADS, COMMANDS_LANE_OBJECT, DATA_LANE_STREET_OBJECT);
		break;
	default:
		break;
	}
	
}

void Draw::DrawObjectInLane(LaneIs laneType){
	switch (laneType) {
	case LaneIs::grass:
		Draw::DrawTree();
		break;
	case LaneIs::street:
		Draw::DrawMultiplePoints(GL_QUADS, COMMANDS_LANE_OBJECT, DATA_LANE_STREET_OBJECT);
		break;
	default:
		break;
	}
}

void Draw::DrawTree() {
	Draw::DrawMultiplePoints(GL_QUADS, COMMANDS_TREE_OBJECT, DATA_TREE_OBJECT);
}

Draw::Draw() {
	player_texture = load_texture("Chicken02Col.jpg");
	tie(player_commands, player_data) = load_obj("Chicken02.obj");
}

void Draw::player() {
	glPushMatrix();
	glScalef(0.5f, 0.5f, 0.5f);
	Draw::DrawMultiplePoints(GL_QUADS, player_commands, player_data, player_texture, true);
	glPopMatrix();
}

void Draw::DrawMultiplePoints(GLenum primitive, vector<char> commands, vector<vector<float>> data, GLuint texture, bool use_texture) {
	glPushMatrix();
	if (use_texture) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture);
	}
	glBegin(primitive);
	for (size_t i = 0; i < commands.size(); i++) {
		switch (commands[i]) {
		case('V'): {
			glVertex3f(data[i][0], data[i][1], data[i][2]);
			break;
		}
		case('T'): {
			glTexCoord2d(data[i][0], data[i][1]);
			break;
		}
		case('N'): {
			glNormal3f(data[i][0], data[i][1], data[i][2]);
			break;
		}
		case('C'): {
			glColor3f(data[i][0], data[i][1], data[i][2]);
			break;
		}
		case('A'): {
			glColor4f(data[i][0], data[i][1], data[i][2], data[i][3]);
			break;
		}
		}
	}
	glEnd();
	if (use_texture) {
		glDisable(GL_TEXTURE_2D);
	}
	glPopMatrix();
}
