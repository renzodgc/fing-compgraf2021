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
	this->directory_path = SAVE_FOLDER + this->current_directory;
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
	return create_directory(directory_path);
}

bool Story::save_result(Image* result, ImageIs type) {
	string file_name;
	switch (type) {
	case ImageIs::FullResult:
		file_name = "\\result.png";
		break;
	case ImageIs::Ambient:
		file_name = "\\x_ambient.png";
		break;
	case ImageIs::Diffuse:
		file_name = "\\x_diffuse.png";
		break;
	case ImageIs::Specular:
		file_name = "\\x_specular.png";
		break;
	case ImageIs::Reflection:
		file_name = "\\x_reflection.png";
		break;
	case ImageIs::Transmission:
		file_name = "\\x_transmission.png";
		break;
	case ImageIs::ColorAmbient:
		file_name = "\\z_ambient.png";
		break;
	case ImageIs::ColorDiffuse:
		file_name = "\\z_diffuse.png";
		break;
	case ImageIs::ColorSpecular:
		file_name = "\\z_specular.png";
		break;
	}
	return save_image(result, directory_path + file_name.c_str());
}

// Aux methods
// -----------------------------------------------------------------------------------

string Story::get_current_time() {
	time_t rawtime;
	struct tm timeinfo;
	char buffer[80];

	time(&rawtime);
	localtime_s(&timeinfo, &rawtime);

	strftime(buffer, sizeof(buffer), "%Y-%m-%d_%H-%M-%S", &timeinfo);
	string str(buffer);

	return str;
}
