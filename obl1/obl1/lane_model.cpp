// HEADERS
// -----------------------------------------------------------------------------------
#include "lane_model.h"

// NAMESPACE
// -----------------------------------------------------------------------------------
using namespace std;

// METHODS
// -----------------------------------------------------------------------------------

// Constructor parent
// -----------------------------------------------------------------------------------

Lane::Lane(float pos_z) {
	lane_position = { 0.f, 0.f, pos_z };
	objects.push_back(new Border({ -LANE_HALF_LENGTH, lane_position.y, lane_position.z }));
	objects.push_back(new Border({ LANE_HALF_LENGTH, lane_position.y, lane_position.z }));

	draw_manager = &Draw::get_instance();
}

// Getters & Setters
// -----------------------------------------------------------------------------------

position Lane::get_lane_position() {
	return lane_position;
}

void Lane::set_lane_position(position pos) {
	lane_position = pos;
}

// Main methods
// -----------------------------------------------------------------------------------

void Lane::draw(bool use_texture) {
	glPushMatrix();
	glTranslatef(lane_position.x, lane_position.y, lane_position.z);

	draw_manager->lane(lane_type, use_texture);
	for (size_t i = 0; i < objects.size(); i++) {
		objects[i]->draw(use_texture);
	}
	glPopMatrix();
}

// Constructors children
// -----------------------------------------------------------------------------------

Grass::Grass(float pos_z): Lane(pos_z) {
	lane_type = LaneIs::grass;
	
	// Get amount of trees
	unsigned int number_of_trees = get_random(LANE_LENGTH / 2);

	// Get random unrepeated positions for trees
	vector<int> positions = get_random_vector(number_of_trees, LANE_LENGTH / 2);

	// Create trees
	for (size_t i = 0; i < number_of_trees; i++) {
		objects.push_back(new Tree({ lane_position.x + positions[i], lane_position.y, lane_position.z }));
	}
}

Street::Street(float pos_z) : Lane(pos_z) {
	lane_type = LaneIs::street;
}
