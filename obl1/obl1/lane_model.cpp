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

Lane::~Lane() {
	// Apply lane_deleter to each element (to free their memory)
	for_each(this->objects.begin(), this->objects.end(), scenario_object_deleter());
	// Delete null elements
	this->objects.erase(this->objects.begin(), this->objects.end());
}

// Getters & Setters
// -----------------------------------------------------------------------------------

Vector3 Lane::get_lane_position() {
	return lane_position;
}

void Lane::set_lane_position(Vector3 pos) {
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

// AABB - AABB Collisions (Axis-aligned bounding box)
// Reference: https://learnopengl.com/In-Practice/2D-Game/Collisions/Collision-detection
vector<OnCollision> Lane::update(double elapsed_time, Vector3 player_position) {
	// Check for collisions only if the player is in or adyacent to this lane.
	vector<OnCollision> collision_events;
	if (abs(lane_position.z - player_position.z) <= 1) {
		bool collision_x, collision_z;
		float player_bounding_box_radius = TILE_LENGTH;
		for (size_t i = 0; i < objects.size(); i++) {
			// Check for overlaping on BOTH the Z and the X axis (Y axis doesn't matter)
			collision_x = (
				((player_position.x + player_bounding_box_radius) > (objects[i]->get_object_position().x - objects[i]->get_bounding_box_radius().x)) &&
				((objects[i]->get_object_position().x + objects[i]->get_bounding_box_radius().x) > (player_position.x - player_bounding_box_radius))
			);
			collision_z = (
				((player_position.z + player_bounding_box_radius) > (objects[i]->get_object_position().z - objects[i]->get_bounding_box_radius().z)) &&
				((objects[i]->get_object_position().z + objects[i]->get_bounding_box_radius().z) > (player_position.z - player_bounding_box_radius))
			);
			if (collision_x && collision_z) {
				collision_events.push_back(objects[i]->get_on_collision_behaviour());
			}
		}
	}
	return collision_events;
}

// Street methods
// -----------------------------------------------------------------------------------

Street::Street(float pos_z, unsigned int level) : Lane(pos_z) {
	lane_type = LaneIs::street;

	// Set speed property
	objects_speed = (float) BASE_SPEED_COEF + (level / (get_random(SPEED_RANDOM_COEF) + 1));

	// Set spawning properties
	spawn_cooldown = (float) BASE_SPAWN_COOLDOWN_COEF / objects_speed;
	spawn_rate = (float) BASE_SPAWN_RATE_COEF + (get_random(SPAWN_RATE_RANDOM_COEF) + 1);
	
	// Set direction for cars
	direction = get_random(2);
	if (direction == 0) {
		direction = -1;
	}

	// Set flag for spawning as ready
	ready_to_spawn = true;
}

vector<OnCollision> Street::update(double elapsed_time, Vector3 player_position) {
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
		if (get_random(100) <= spawn_rate * elapsed_time) {
			ready_to_spawn = false;
			current_cooldown = spawn_cooldown;
			objects.push_back(new Car({ lane_position.x - LANE_HALF_LENGTH * direction, lane_position.y, lane_position.z }, direction));
		}
	}

	// Check for collisions
	return Lane::update(elapsed_time, player_position);
}

// Grass methods
// -----------------------------------------------------------------------------------

Grass::Grass(float pos_z) : Lane(pos_z) {
	lane_type = LaneIs::grass;
	
	// Get amount of trees
	unsigned int number_of_trees = get_random(LANE_LENGTH / 3);

	// Get random unrepeated positions for trees. Exclude borders
	vector<int> positions = get_random_vector(number_of_trees, (LANE_LENGTH / 2) - 1);

	// If lane is -1, 0 or 1 remove objects adyacent to player spawn position
	if (pos_z >= -1 && pos_z <= 1) {
		positions.erase(remove_if(positions.begin(), positions.end(), is_zero_one_or_minus_one), positions.end());
	}

	// Create trees
	for (size_t i = 0; i < positions.size(); i++) {
		objects.push_back(new Tree({ lane_position.x + positions[i], lane_position.y, lane_position.z }));
	}
}

// Wall methods
// -----------------------------------------------------------------------------------

Wall::Wall(float pos_z) : Lane(pos_z) {
	lane_type = LaneIs::wall;
}

vector<OnCollision> Wall::update(double elapsed_time, Vector3 player_position) {
	// Check for collisions only if the player is in or adyacent to this lane.
	vector<OnCollision> collision_events;
	if (abs(lane_position.z - player_position.z) <= 1) {
		float player_bounding_box_radius = TILE_LENGTH;
		float lane_bounding_box_radius = TILE_LENGTH;
		// Check for overlaping on the Z axis
		bool collision_z = (
			((player_position.z + player_bounding_box_radius) > (lane_position.z - lane_bounding_box_radius)) &&
			((lane_position.z + lane_bounding_box_radius) > (player_position.z - player_bounding_box_radius))
			);
		if (collision_z) {
			collision_events.push_back(OnCollision::bounce);
		}
	}
	return collision_events;
}
