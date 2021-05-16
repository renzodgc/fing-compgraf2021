#include "scenario_object_model.h"

// GENERIC

ScenarioObject::ScenarioObject(position pos) {
	object_position = pos;
	draw_manager = &Draw::get_instance();
	on_collision_behaviour = OnCollision::bounce;
}

position ScenarioObject::get_object_position() {
	return object_position;
}

void ScenarioObject::set_object_position(position pos) {
	object_position = pos;
}

vector3d ScenarioObject::get_bounding_box_radius() {
	return bounding_box_radius;
}
void ScenarioObject::set_bounding_box_radius(vector3d radius) {
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

Tree::Tree(position pos) : ScenarioObject(pos) {
	object_type = ObjectIs::tree;
	on_collision_behaviour = OnCollision::bounce;
	bounding_box_radius = { 0.5f, 0.5f, 0.5f };
}

void Tree::draw(bool use_texture) {
	glPushMatrix();
	glTranslatef(object_position.x, 0.f, 0.f);
	draw_manager->tree(use_texture);
	glPopMatrix();
}

// BORDER

Border::Border(position pos) : ScenarioObject(pos) {
	object_type = ObjectIs::border;
	on_collision_behaviour = OnCollision::bounce;
	bounding_box_radius = { 0.5f, 0.5f, 0.5f };
}

void Border::draw(bool use_texture) {
	glPushMatrix();
	glTranslatef(object_position.x, 0.f, 0.f);
	glScalef(1.f, 3.f, 1.f);
	draw_manager->border(use_texture);
	glPopMatrix();
}


// CAR

Car::Car(position pos, int direct) : ScenarioObject(pos) {
	object_type = ObjectIs::car;
	direction = direct;
	on_collision_behaviour = OnCollision::death;
	bounding_box_radius = { 1.f, 0.5f, 0.5f };
}

void Car::draw(bool use_texture) {
	glPushMatrix();
	glTranslatef(object_position.x, -0.25f, 0.f);
	if (direction == -1) {
		glRotatef(180.f, 0.f, 1.f, 0.f);
	}
	draw_manager->car(use_texture);
	glPopMatrix();
}
