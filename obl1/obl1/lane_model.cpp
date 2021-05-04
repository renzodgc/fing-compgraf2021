// HEADERS
// -----------------------------------------------------------------------------------
#include "lane_model.h"
#include "draw_manager.h"

// NAMESPACE
// -----------------------------------------------------------------------------------
using namespace std;

// METHODS
// -----------------------------------------------------------------------------------

// GENERIC

Lane::Lane(position pos, LaneIs type) {
	lane_position = pos;
	lane_type = type;
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

	glPopMatrix();
}
