#include "utils.h"


using namespace std;

tuple<SDL_Window*, SDL_GLContext> InitializeSDL(string program_name, int scr_width, int scr_height) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cerr << "[Error]: No se pudo iniciar SDL: " << SDL_GetError() << endl;
		exit(1);
	}
	SDL_Window* window = SDL_CreateWindow(
		program_name.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		scr_width, scr_height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
	);
	if (window == NULL) {
		cerr << "[Video Error]: " << SDL_GetError() << endl;
		SDL_Quit();
		exit(1);
	}
	SDL_GLContext context = SDL_GL_CreateContext(window);
	if (window == NULL) {
		cerr << "[GL Context Error]: " << SDL_GetError() << endl;
		SDL_Quit();
		exit(1);
	}
	return {window, context};
}

void ToggleFullscreen(SDL_Window* Window) {
	Uint32 FullscreenFlag = SDL_WINDOW_FULLSCREEN;
	bool IsFullscreen = SDL_GetWindowFlags(Window) & FullscreenFlag;
	SDL_SetWindowFullscreen(Window, IsFullscreen ? 0 : FullscreenFlag);
	SDL_ShowCursor(IsFullscreen);
}

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

void DrawTriangle(triangle triangle) {
	glBegin(GL_TRIANGLES);
		glColor3f(triangle.color.red, triangle.color.green, triangle.color.blue);
		glVertex3f(triangle.a.x, triangle.a.y, triangle.a.z);
		glVertex3f(triangle.b.x, triangle.b.y, triangle.b.z);
		glVertex3f(triangle.c.x, triangle.c.y, triangle.c.z);
	glEnd();
}

void DrawMulticoloredTriangle(multicolored_triangle triangle) {
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < 3; i++) {
		glColor3f(triangle.color_a.red, triangle.color_a.green, triangle.color_a.blue);
		glVertex3f(triangle.a.x, triangle.a.y, triangle.a.z);
		glColor3f(triangle.color_b.red, triangle.color_b.green, triangle.color_b.blue);
		glVertex3f(triangle.b.x, triangle.b.y, triangle.b.z);
		glColor3f(triangle.color_c.red, triangle.color_c.green, triangle.color_c.blue);
		glVertex3f(triangle.c.x, triangle.c.y, triangle.c.z);
	}
	glEnd();
}

void DrawSquare(square square) {
	glBegin(GL_QUADS);
		glColor3f(square.color.red, square.color.green, square.color.blue);
		glVertex3f(square.a.x, square.a.y, square.a.z);
		glVertex3f(square.b.x, square.b.y, square.b.z);
		glVertex3f(square.c.x, square.c.y, square.c.z);
		glVertex3f(square.d.x, square.d.y, square.d.z);
	glEnd();
}

void DrawTexturedSquare(GLuint texture, textured_square square) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUADS);
		glColor3f(square.color.red, square.color.green, square.color.blue);
		glTexCoord2f(square.tex_a.x, square.tex_a.y); glVertex3f(square.a.x, square.a.y, square.a.z);
		glTexCoord2f(square.tex_b.x, square.tex_b.y); glVertex3f(square.b.x, square.b.y, square.b.z);
		glTexCoord2f(square.tex_c.x, square.tex_c.y); glVertex3f(square.c.x, square.c.y, square.c.z);
		glTexCoord2f(square.tex_d.x, square.tex_d.y); glVertex3f(square.d.x, square.d.y, square.d.z);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void DrawMultiplePoints(GLenum primitive, vector<char> commands, vector<vector<float>> data) {
	glBegin(primitive);
	for (size_t i = 0; i < commands.size(); i++) {
		switch (commands[i]) {
			case('C'): {
				glColor3f(data[i][0], data[i][1], data[i][2]);
				break;
			}
			case('V'): {
				glVertex3f(data[i][0], data[i][1], data[i][2]);
				break;
			}
			case('N'): {
				glNormal3f(data[i][0], data[i][1], data[i][2]);
				break;
			}
		}
	}
	glEnd();
}


position normalize_vector(position pos) {
	float magnitude = sqrt(pow(pos.x, 2) + pow(pos.y, 2) + pow(pos.z, 2));
	if (magnitude == 0.f) { return { 0.f, 0.f, 0.f }; }
	return { pos.x / magnitude, pos.y / magnitude, pos.z / magnitude };
}

position cross_product_vector(position a, position b) {
	return {
		a.y * b.z - a.z * b.y,
		-(a.x * b.z - a.z * b.x),
		a.x * b.y - a.y * b.x
	};
}

float degree_to_radian(float degree) {
	float pi = 3.14159265359f;
	return(degree * (pi / 180.f));
}