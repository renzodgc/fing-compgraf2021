// HEADERS
// -----------------------------------------------------------------------------------
#include "file_helper.h"

// NAMESPACE
// -----------------------------------------------------------------------------------
using namespace std;

// METHODS
// -----------------------------------------------------------------------------------
 
GLuint LoadTexture(string texture_file) {
	// Load texture's image
	FREE_IMAGE_FORMAT fif = FreeImage_GetFIFFromFilename(texture_file.c_str());
	FIBITMAP* bitmap = FreeImage_Load(fif, texture_file.c_str());
	bitmap = FreeImage_ConvertTo24Bits(bitmap);
	int texture_width = FreeImage_GetWidth(bitmap);
	int texture_height = FreeImage_GetHeight(bitmap);
	void* data = FreeImage_GetBits(bitmap);

	// Apply texture
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture_width, texture_height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	return texture;
}
 
tuple<vector<char>, vector<vector<float>>> LoadTrianglePolygonFile(string texture_file) {
	ifstream file_stream(texture_file);
	vector<char> commands;
	vector<vector<float>> data;

	char command;
	float x, y, z;

	while (file_stream >> command >> x >> y >> z) {
		commands.push_back(command);
		data.push_back({ x, y, z });
	}
	return { commands, data };
}

