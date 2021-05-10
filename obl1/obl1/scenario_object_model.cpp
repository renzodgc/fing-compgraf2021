#include "scenario_object_model.h"

Tree::Tree(position pos) : ScenarioObject(pos) {
	object_type = ObjectIs::tree;
}

void Tree::draw() {
	glTranslatef(object_position.x, object_position.y, object_position.z);
	DrawTree();
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
