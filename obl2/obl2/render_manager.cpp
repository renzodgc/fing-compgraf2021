// HEADERS
// -----------------------------------------------------------------------------------
#include "render_manager.h"

// NAMESPACE
// -----------------------------------------------------------------------------------
using namespace std;

// METHODS
// -----------------------------------------------------------------------------------

// Constructor and Singleton method
// -----------------------------------------------------------------------------------

Render::Render() {}

Render& Render::get_instance() {
	static Render instance; // Guaranteed to be destroyed. Instantiated on first use.
	return instance;
}
