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

Scene::Scene() {}

Scene& Scene::get_instance() {
	static Scene instance; // Guaranteed to be destroyed. Instantiated on first use.
	return instance;
}
