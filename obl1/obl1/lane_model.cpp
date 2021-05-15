// HEADERS
// -----------------------------------------------------------------------------------
#include "lane_model.h"

// NAMESPACE
// -----------------------------------------------------------------------------------
using namespace std;

// METHODS
// -----------------------------------------------------------------------------------

// Constructor
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

void Lane::update(double elapsed_time) {
	// coins here
}

// Street methods
// -----------------------------------------------------------------------------------

Street::Street(float pos_z) : Lane(pos_z) {
	lane_type = LaneIs::street;

	objects_speed = (float)((rand() % 4) + 2);
	// TODO: Revisar
	spawn_cooldown = 2.5f / objects_speed;
	spawn_rate = (float)((rand() % 40) + 25);
	ready_to_spawn = true;
	direction = rand() % 2;
	if (direction == 0) {
		direction = -1;
	}
}

void Street::update(double elapsed_time) {
	Lane::update(elapsed_time);

	vector<int> objects_indices_to_destroy;
	for (size_t i = 0; i < objects.size(); i++) {
		if (objects[i]->get_object_type() == ObjectIs::car) {
			// 1. Move the objects
			float x = objects[i]->get_object_position().x;
			objects[i]->set_object_x(x + (float)(objects_speed * elapsed_time * direction));
			// 2. Mark to destroy the objects out of bounds
			if (abs(x) > LANE_HALF_LENGTH) {
				objects_indices_to_destroy.push_back(i);
			}
		}
	}

	// 3. Destroy objects out of bounds
	for (size_t i = 0; i < objects_indices_to_destroy.size(); i++) {
		delete objects[objects_indices_to_destroy[i]];
		objects.erase(objects.begin() + objects_indices_to_destroy[i]);
	}

	// 4. Spawn new objects
	if (!ready_to_spawn) {
		current_cooldown -= elapsed_time;
		if (current_cooldown <= 0) {
			ready_to_spawn = true;
		}
	}

	if (ready_to_spawn) {
		// Throw a dice
		if (((rand() % 100)) <= spawn_rate * elapsed_time) {
			ready_to_spawn = false;
			current_cooldown = spawn_cooldown;
			objects.push_back(new Car({ lane_position.x - LANE_HALF_LENGTH * direction, lane_position.y, lane_position.z }, direction));
		}
	}

}

// Grass methods
// -----------------------------------------------------------------------------------

Grass::Grass(float pos_z) : Lane(pos_z) {
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
