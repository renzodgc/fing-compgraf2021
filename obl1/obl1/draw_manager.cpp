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
	grass_texture = load_texture(ROUTE_GRASS_TEXTURE);
	wood_texture = load_texture(ROUTE_WOOD_TEXTURE);
	street_texture = load_texture(ROUTE_STREET_TEXTURE);
	leaves_texture = load_texture(ROUTE_LEAVES_TEXTURE);
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
		DrawMultiplePoints(GL_QUADS, COMMANDS_LANE_WALL_OBJECT, DATA_LANE_WALL_OBJECT);
		break;
	case LaneIs::grass:
		DrawMultiplePoints(GL_QUADS, COMMANDS_GRASS_OBJECT, DATA_LANE_GRASS_OBJECT, grass_texture, use_texture);
		break;
	case LaneIs::street:
		DrawMultiplePoints(GL_QUADS, COMMANDS_STREET_OBJECT, DATA_LANE_STREET_OBJECT, street_texture, use_texture);
		break;
	}
}

void Draw::border(bool use_texture) {
	DrawMultiplePoints(GL_QUADS, COMMANDS_CUBE_OBJECT, DATA_CUBE_OBJECT);
}

void Draw::tree(bool use_texture) {
	DrawMultiplePoints(GL_QUADS, COMMANDS_TREE_STUMP_OBJECT, DATA_TREE_STUMP_OBJECT, wood_texture, use_texture);
	DrawMultiplePoints(GL_QUADS, COMMANDS_TREE_LEAVES_OBJECT, DATA_TREE_LEAVES_OBJECT, leaves_texture, use_texture);
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
		glColor3f(1.f, 1.f, 1.f);
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
			if (!use_texture) {
				glColor3f(data[i][0], data[i][1], data[i][2]);
			}
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
