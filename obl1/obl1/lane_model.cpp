// HEADERS
// -----------------------------------------------------------------------------------
#include "lane_model.h"

// NAMESPACE
// -----------------------------------------------------------------------------------
using namespace std;

// METHODS
// -----------------------------------------------------------------------------------

// GENERIC

Lane::Lane(float pos_z) {
	lane_position = { 0.f, 0.f, pos_z };
	objects.push_back(new Border({ -LANE_HALF_LENGTH, lane_position.y, lane_position.z }));
	objects.push_back(new Border({ LANE_HALF_LENGTH, lane_position.y, lane_position.z }));
}

position Lane::get_lane_position() {
	return lane_position;
}

void Lane::set_lane_position(position pos) {
	lane_position = pos;
}

void Lane::draw() {
	glPushMatrix();
	glTranslatef(lane_position.x, lane_position.y, lane_position.z);

	Draw::DrawLane(lane_type);
	for (size_t i = 0; i < objects.size(); i++) {
		objects[i]->draw();
	}
	glPopMatrix();
}

Grass::Grass(float pos_z): Lane(pos_z) {
	lane_type = LaneIs::grass;
	int number_of_trees = rand() % LANE_LENGTH / 2;

	for (size_t i = 0; i < number_of_trees; i++) {
		int offset_x = (rand() % (LANE_LENGTH - 1)) - ( LANE_LENGTH / 2 - 1 );
		objects.push_back(new Tree({ lane_position.x + offset_x, lane_position.y, lane_position.z }));
	}
}

Street::Street(float pos_z) : Lane(pos_z) {
	lane_type = LaneIs::street;
}
