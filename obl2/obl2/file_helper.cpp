// HEADERS
// -----------------------------------------------------------------------------------
#include "file_helper.h"

// NAMESPACE
// -----------------------------------------------------------------------------------
using namespace std;

// METHODS
// -----------------------------------------------------------------------------------

bool create_directory(string path) {
	return CreateDirectory(path.c_str(), NULL) != 0;
}

bool save_image(Image* image, string file_name) {
	FIBITMAP* bitmap = image->float_to_bitmap();
	return FreeImage_Save(FIF_PNG, bitmap, file_name.c_str(), 0);
}
