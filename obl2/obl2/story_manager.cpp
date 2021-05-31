// HEADERS
// -----------------------------------------------------------------------------------
#include "story_manager.h"

// NAMESPACE
// -----------------------------------------------------------------------------------
using namespace std;

// METHODS
// -----------------------------------------------------------------------------------

// Constructor and Singleton method
// -----------------------------------------------------------------------------------

Story::Story() {}

Story& Story::get_instance() {
	static Story instance; // Guaranteed to be destroyed. Instantiated on first use.
	return instance;
}
