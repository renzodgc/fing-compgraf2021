#include "scenario_object_model.h"

// GENERIC

ScenarioObject::ScenarioObject(position pos) {
	object_position = pos;
	draw_manager = &Draw::get_instance();
}

position ScenarioObject::get_object_position() {
	return object_position;
}

void ScenarioObject::set_object_position(position pos) {
	object_position = pos;
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
}

void Border::draw(bool use_texture) {
	glPushMatrix();
	glTranslatef(object_position.x, 0.f, 0.f);
	glScalef(1.f, 3.f, 1.f);
	draw_manager->border(use_texture);
	glPopMatrix();
}


// CAR

Car::Car(position pos, float vel) : ScenarioObject(pos) {
	object_type = ObjectIs::car;
	velocity = vel;
	initial_position = pos;
}

void Car::draw(bool use_texture) {
	if (object_position.x > LANE_HALF_LENGTH) {
		object_position.x = initial_position.x;
	}
	glPushMatrix();
	object_position.x += velocity * 0.03f;
	glTranslatef(object_position.x, 0.f, 0.f);
	draw_manager->car(use_texture);
	glPopMatrix();
}
