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
