// HEADERS
// -----------------------------------------------------------------------------------
#include "lane_model.h"

// NAMESPACE
// -----------------------------------------------------------------------------------
using namespace std;

// METHODS
// -----------------------------------------------------------------------------------

// GENERIC

Lane::Lane(position pos) {
	lane_position = pos;
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

	DrawLane(lane_type);
	
	for (size_t i = 0; i < objects.size(); i++) {
		objects[i]->draw();
	}

	glPopMatrix();
}

Grass::Grass(position pos): Lane(pos) {
	lane_type = LaneIs::grass;

	int number_of_trees = rand() % LANE_LENGTH / 2;

	for (size_t i = 0; i < number_of_trees; i++) {
		int offset_x = (rand() % LANE_LENGTH) - ( LANE_LENGTH / 2 );
		cout << pos.x + offset_x << endl;
		objects.push_back(new Tree({ pos.x + offset_x, pos.y, pos.z }));
	}
}

Street::Street(position pos) : Lane(pos) {
	lane_type = LaneIs::street;
	/*objects = {  }*/
}