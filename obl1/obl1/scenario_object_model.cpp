#include "scenario_object_model.h"

// GENERIC

ScenarioObject::ScenarioObject(position pos) {
	object_position = pos;
	draw_manager = &Draw::get_instance();
}

position ScenarioObject::get_object_position() {
	return position();
}

void ScenarioObject::set_object_position(position pos) {
	object_position = pos;
}

// TREE

Tree::Tree(position pos) : ScenarioObject(pos) {
	object_type = ObjectIs::tree;
}

void Tree::draw() {
	glPushMatrix();
	glTranslatef(object_position.x, 0.f, 0.f);
	Draw::DrawTree();
	glPopMatrix();
}

// BORDER

Border::Border(position pos) : ScenarioObject(pos) {
	object_type = ObjectIs::border;
}

void Border::draw() {
	glPushMatrix();
	glTranslatef(object_position.x, 0.f, 0.f);
	glScalef(1.f, 3.f, 1.f);
	Draw::DrawCube();
	glPopMatrix();
}


// CAR

Car::Car(position pos) : ScenarioObject(pos) {
	object_type = ObjectIs::car;
}

void Car::draw() {
}
