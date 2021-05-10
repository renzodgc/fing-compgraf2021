// HEADERS
// -----------------------------------------------------------------------------------
#include "file_helper.h"

// NAMESPACE
// -----------------------------------------------------------------------------------
using namespace std;

// METHODS
// -----------------------------------------------------------------------------------
 
GLuint load_texture(string texture_file) {
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
 
// References: https://en.wikibooks.org/wiki/OpenGL_Programming/Modern_OpenGL_Tutorial_Load_OBJ
// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/
tuple<vector<char>, vector<vector<float>>> load_obj(string file) {
	ifstream file_stream(file);
	if (!file_stream) {
		cerr << "Cannot open: " << file << endl;
		exit(1);
	}
	vector<char> commands;
	vector<vector<float>> data;

	vector<unsigned int> vertex_indices, uv_indices, normal_indices;
	vector<vector<float>> temp_vertices, temp_uvs, temp_normals;

	string line, subline, command, face1, face2, face3, face4;
	vector<string> faces;
	float x, y, z;
	unsigned int aux;

	while (getline(file_stream, line)) {
		file_stream >> command;

		if (command == "v") {
			file_stream >> x >> y >> z;
			temp_vertices.push_back({ x, y, z });
		} else if(command == "vt") {
			file_stream >> x >> y;
			temp_uvs.push_back({ x, y });
		} else if(command == "vn") {
			file_stream >> x >> y >> z;
			temp_normals.push_back({ x, y, z });
		} else if (command == "f") {
			file_stream >> face1 >> face2 >> face3 >> face4;
			faces = { face1, face2, face3, face4 };
			for (size_t i = 0; i < faces.size(); i++) {
				istringstream sub_stream(faces[i]);
				getline(sub_stream, subline, '/');
				if (stoi(subline) < 0) {
					aux = temp_vertices.size() - stoi(subline);
				} else {
					aux = stoi(subline) - 1;
				}
				vertex_indices.push_back(aux);

				getline(sub_stream, subline, '/');
				if (stoi(subline) < 0) {
					aux = temp_uvs.size() - stoi(subline);
				} else {
					aux = stoi(subline) - 1;
				}
				uv_indices.push_back(aux);

				getline(sub_stream, subline, '/');
				if (stoi(subline) < 0) {
					aux = temp_normals.size() - stoi(subline);
				} else {
					aux = stoi(subline) - 1;
				}
				normal_indices.push_back(aux);
			}
		}
	}
	commands.push_back('C');
	data.push_back({ 1.f, 1.f, 1.f });
	for(size_t i = 0; i < uv_indices.size(); i++) {
		commands.push_back('T'); data.push_back(temp_uvs[uv_indices[i]]);
		commands.push_back('N'); data.push_back(temp_normals[normal_indices[i]]);
		commands.push_back('V'); data.push_back(temp_vertices[vertex_indices[i]]);
	}

	return { commands, data };
}

