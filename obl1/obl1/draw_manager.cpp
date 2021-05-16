// HEADERS
// -----------------------------------------------------------------------------------
#include "draw_manager.h"

// NAMESPACE
// -----------------------------------------------------------------------------------
using namespace std;

// METHODS
// -----------------------------------------------------------------------------------

// Constructor and Singleton method
// -----------------------------------------------------------------------------------

Draw::Draw() {
	player_texture = load_texture(ROUTE_PLAYER_TEXTURE);
	tie(player_commands, player_data) = load_obj(ROUTE_PLAYER_OBJECT, ObjType::squares);
	car_texture = load_texture(ROUTE_CAR_TEXTURE);
	tie(car_commands, car_data) = load_obj(ROUTE_CAR_OBJECT, ObjType::triangles);
}

Draw& Draw::get_instance() {
	static Draw instance; // Guaranteed to be destroyed. Instantiated on first use.
	return instance;
}

// Main objects' drawing methods
// -----------------------------------------------------------------------------------

void Draw::player(bool use_texture) {
	glPushMatrix();
	glScalef(0.5f, 0.5f, 0.5f);
	DrawMultiplePoints(GL_QUADS, player_commands, player_data, player_texture, use_texture);
	glPopMatrix();
}

void Draw::lane(LaneIs laneType, bool use_texture) {
	switch (laneType) {
	case LaneIs::wall:
		DrawMultiplePoints(GL_QUADS, COMMANDS_LANE_OBJECT, DATA_LANE_WALL_OBJECT);
		break;
	case LaneIs::grass:
		DrawMultiplePoints(GL_QUADS, COMMANDS_LANE_OBJECT, DATA_LANE_GRASS_OBJECT);
		break;
	case LaneIs::street:
		DrawMultiplePoints(GL_QUADS, COMMANDS_LANE_OBJECT, DATA_LANE_STREET_OBJECT);
		break;
	}
}

void Draw::border(bool use_texture) {
	DrawMultiplePoints(GL_QUADS, COMMANDS_CUBE_OBJECT, DATA_CUBE_OBJECT);
}

void Draw::tree(bool use_texture) {
	DrawMultiplePoints(GL_QUADS, COMMANDS_TREE_OBJECT, DATA_TREE_OBJECT);
}

void Draw::car(bool use_texture) {
	DrawMultiplePoints(GL_TRIANGLES, car_commands, car_data, car_texture, use_texture);
}


// Primitive objects' drawing methods
// -----------------------------------------------------------------------------------

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

void Draw::DrawMultiplePoints(GLenum primitive, vector<char> commands, vector<vector<float>> data) {
	DrawMultiplePoints(primitive, commands, data, NULL, false);
}

void Draw::DrawHUD(HUDComponent left, HUDComponent right) {
	glPushMatrix();
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
	glPopMatrix();
}

void Draw::DrawHUDComponent(HUDComponent component) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, component.texture_id);
	glColor3f(component.message_color.r, component.message_color.g, component.message_color.b);
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

// Other objects' drawing methods
// -----------------------------------------------------------------------------------

void Draw::DrawReferenceObject() {
	DrawMultiplePoints(GL_QUADS, COMMANDS_REFERENCE_OBJECT, DATA_REFERENCE_OBJECT);
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
