#include "scenario_object_model.h"

Tree::Tree(position pos) : ScenarioObject(pos) {
	object_type = ObjectIs::tree;
}

void Tree::draw() {
	glPushMatrix();
	glTranslatef(object_position.x, 0.f, 0.f);
	Draw::DrawTree();
	glPopMatrix();
}

Car::Car(position pos) : ScenarioObject(pos) {
	object_type = ObjectIs::car;
}

void Car::draw() {
}

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


ScenarioObject::ScenarioObject(position pos)
{
	object_position = pos;
}

position ScenarioObject::get_object_position()
{
	return position();
}

void ScenarioObject::set_object_position(position pos)
{
	object_position = pos;
}
