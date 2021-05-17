// HEADERS
// -----------------------------------------------------------------------------------
#include "scenario_object_model.h"

// NAMESPACE
// -----------------------------------------------------------------------------------
using namespace std;

// METHODS
// -----------------------------------------------------------------------------------

// Constructor
// -----------------------------------------------------------------------------------

ScenarioObject::ScenarioObject(Vector3 pos) {

	// References
	draw_manager = &Draw::get_instance();

	// Basic properties
	object_position = pos;
	on_collision_behaviour = OnCollision::bounce;
}

// Helpers
bool ScenarioObject::should_be_drawn() {
	return !(FRUSTUM_CULLING && (FrustumGeometric::get_instance().sphere_in_frustum(object_position, TILE_LENGTH) == FrustumGeometric::OUTSIDE));
}

// Getters & Setters
// -----------------------------------------------------------------------------------

Vector3 ScenarioObject::get_object_position() {
	return object_position;
}
void ScenarioObject::set_object_position(Vector3 pos) {
	object_position = pos;
}

Vector3 ScenarioObject::get_bounding_box_radius() {
	return bounding_box_radius;
}
void ScenarioObject::set_bounding_box_radius(Vector3 radius) {
	bounding_box_radius = radius;
}

OnCollision ScenarioObject::get_on_collision_behaviour() {
	return on_collision_behaviour;
}
void ScenarioObject::set_on_collision_behaviour(OnCollision behaviour) {
	on_collision_behaviour = behaviour;
}

void ScenarioObject::set_object_x(float x) {
	object_position.x = x;
}

ObjectIs ScenarioObject::get_object_type() {
	return object_type;
}
void ScenarioObject::set_object_type(ObjectIs type) {
	object_type = type;
}

// TREE
// -----------------------------------------------------------------------------------

// Constructor
// -----------------------------------------------------------------------------------

Tree::Tree(Vector3 pos) : ScenarioObject(pos) {

	// Basic properties
	object_type = ObjectIs::tree;
	on_collision_behaviour = OnCollision::bounce;
	bounding_box_radius = { 0.5f, 0.5f, 0.5f };
}

// Main methods
// -----------------------------------------------------------------------------------

void Tree::draw(bool use_texture) {
	if (should_be_drawn()) {
		glPushMatrix();
		glTranslatef(object_position.x, 0.f, 0.f);
		draw_manager->tree(use_texture);
		glPopMatrix();
	}
}

// BORDER
// -----------------------------------------------------------------------------------

// Constructor
// -----------------------------------------------------------------------------------

Border::Border(Vector3 pos) : ScenarioObject(pos) {

	// Basic properties
	object_type = ObjectIs::border;
	on_collision_behaviour = OnCollision::bounce;
	bounding_box_radius = { 0.5f, 0.5f, 0.5f };
}

// Main methods
// -----------------------------------------------------------------------------------

void Border::draw(bool use_texture) {
	if (should_be_drawn()) {
		glPushMatrix();
		glTranslatef(object_position.x, 0.f, 0.f);
		glScalef(1.f, 3.f, 1.f);
		draw_manager->border(use_texture);
		glPopMatrix();
	}
}

// CAR
// -----------------------------------------------------------------------------------

// Constructor
// -----------------------------------------------------------------------------------

Car::Car(Vector3 pos, int direct) : ScenarioObject(pos) {
	
	// Basic properties
	object_type = ObjectIs::car;
	on_collision_behaviour = OnCollision::death;
	bounding_box_radius = { 1.f, 0.5f, 0.5f };

	// Other properties
	direction = direct;
}

// Main methods
// -----------------------------------------------------------------------------------

void Car::draw(bool use_texture) {
	if (should_be_drawn()) {
		glPushMatrix();
		glTranslatef(object_position.x, -0.25f, 0.f);
		if (direction == -1) {
			glRotatef(180.f, 0.f, 1.f, 0.f);
		}
		draw_manager->car(use_texture);
		glPopMatrix();
	}
}
