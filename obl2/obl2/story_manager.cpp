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

Story::Story() {
	this->current_directory = get_current_time();
	this->created = create_current_directory();
}

Story& Story::get_instance() {
	static Story instance; // Guaranteed to be destroyed. Instantiated on first use.
	return instance;
}

// Getters & Setters
// -----------------------------------------------------------------------------------

bool Story::is_created() {
	return this->created;
}


// Main methods
// -----------------------------------------------------------------------------------

bool Story::create_current_directory() {
	return create_directory(SAVE_FOLDER + this->current_directory);
}

// Aux methods
// -----------------------------------------------------------------------------------

string Story::get_current_time() {
	time_t rawtime;
	struct tm timeinfo;
	char buffer[80];

	time(&rawtime);
	localtime_s(&timeinfo, &rawtime);

	strftime(buffer, sizeof(buffer), "%Y-%m-%d %H-%M-%S", &timeinfo);
	string str(buffer);

	return str;
}
