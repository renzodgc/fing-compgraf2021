// HEADERS
// -----------------------------------------------------------------------------------
#include "scene_manager.h"

// NAMESPACE
// -----------------------------------------------------------------------------------
using namespace std;

// METHODS
// -----------------------------------------------------------------------------------

// Constructor and Singleton method
// -----------------------------------------------------------------------------------

Scene::Scene() {
	load_scene();
}

Scene& Scene::get_instance() {
	static Scene instance; // Guaranteed to be destroyed. Instantiated on first use.
	return instance;
}

// Main Methods
// -----------------------------------------------------------------------------------

void Scene::load_scene() {

	this->camera = new Camera(new Vector(0, 0, 0), make_pair(0, 0));
	this->lights = {};
	this->objects = {};

}