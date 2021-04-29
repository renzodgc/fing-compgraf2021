// HEADERS
// -----------------------------------------------------------------------------------
#include "camera_helper.h"

// NAMESPACE
// -----------------------------------------------------------------------------------
using namespace std;

// METHODS
// -----------------------------------------------------------------------------------


// ORTHOGONAL CAMERA

// Reference: https://stackoverflow.com/questions/1059200/true-isometric-projection-with-opengl
// Read reference for 2d view
void IsometricCamera::start_isometric_view(position player_position, camera& new_camera) {
	float distance = (float)sqrt(1 / 3.0);
	double scale = 10.;

	new_camera = {
		{ 1.f, 1.f, 1.f },	// camera_eye
		{ 0.f, 0.f, 0.f },  // camera_front
		{ 0.f, 1.f, 0.f },  // camera_up
		-90.0f,				// yaw - Initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
		0.0f				// pitch
	};

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); // Reset the view

	glClearColor(LIGHT_GREY.red, LIGHT_GREY.green, LIGHT_GREY.blue, LIGHT_GREY.alpha);
	glOrtho(-scale, scale, -scale * 0.7, scale * 0.7, -scale, scale);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); // Reset the view

	glRotatef(35.264f, 1.0f, 0.0f, 0.0f);
	glRotatef(-45.0f, 0.0f, 1.0f, 0.0f);
}

// THIRD PERSON CAMERA
void ThirdPersonCamera::start_third_person_view(position player_position, camera& new_camera) {
	new_camera = {
		{ 0.f, 0.f, 1.f },	// camera_eye
		{ 0.f, 0.f, -1.f }, // camera_front
		{ 0.f, 1.f, 0.f },  // camera_up
		-90.0f,				// yaw - Initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
		0.0f				// pitch
	};

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); // Reset the view

	glClearColor(LIGHT_GREY.red, LIGHT_GREY.green, LIGHT_GREY.blue, LIGHT_GREY.alpha);
	gluPerspective(45., SCR_WIDTH / (float)SCR_HEIGHT, 0.1, 100.);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); // Reset the view
}

// FREE CAMERA

void FreeViewCamera::start_free_view(position player_position, camera& new_camera) {
	new_camera = {
		{ 0.f, 0.f, 1.f },	// camera_eye
		{ 0.f, 0.f, -1.f }, // camera_front
		{ 0.f, 1.f, 0.f },  // camera_up
		-90.0f,				// yaw - Initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
		0.0f				// pitch
	};

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); // Reset the view

	glClearColor(LIGHT_GREY.red, LIGHT_GREY.green, LIGHT_GREY.blue, LIGHT_GREY.alpha);
	gluPerspective(45., SCR_WIDTH / (float)SCR_HEIGHT, 0.1, 100.);
	glEnable(GL_DEPTH_TEST);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); // Reset the view
}

void FreeViewCamera::update_camera_front(float mouse_offset_x, float mouse_offset_y, camera& current_camera) {
	current_camera.yaw += mouse_offset_x;
	current_camera.pitch += mouse_offset_y;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (current_camera.pitch > 89.0f)
		current_camera.pitch = 89.0f;
	if (current_camera.pitch < -89.0f)
		current_camera.pitch = -89.0f;

	current_camera.camera_front = normalize_vector({
		cos(degree_to_radian(current_camera.yaw)) * cos(degree_to_radian(current_camera.pitch)),
		sin(degree_to_radian(current_camera.pitch)),
		sin(degree_to_radian(current_camera.yaw)) * cos(degree_to_radian(current_camera.pitch))
	});
}

void FreeViewCamera::update_camera_eye(float camera_speed, const Uint8* keyboard_state, camera& current_camera) {
	if (keyboard_state[SDL_SCANCODE_UP] || keyboard_state[SDL_SCANCODE_W]) {
		current_camera.camera_eye.x += camera_speed * current_camera.camera_front.x;
		current_camera.camera_eye.y += camera_speed * current_camera.camera_front.y;
		current_camera.camera_eye.z += camera_speed * current_camera.camera_front.z;
	}
	if (keyboard_state[SDL_SCANCODE_RIGHT] || keyboard_state[SDL_SCANCODE_D]) {
		position normalized_front_up = normalize_vector(cross_product_vector(current_camera.camera_front, current_camera.camera_up));
		current_camera.camera_eye.x += camera_speed * normalized_front_up.x;
		current_camera.camera_eye.y += camera_speed * normalized_front_up.y;
		current_camera.camera_eye.z += camera_speed * normalized_front_up.z;
	}
	if (keyboard_state[SDL_SCANCODE_DOWN] || keyboard_state[SDL_SCANCODE_S]) {
		current_camera.camera_eye.x -= camera_speed * current_camera.camera_front.x;
		current_camera.camera_eye.y -= camera_speed * current_camera.camera_front.y;
		current_camera.camera_eye.z -= camera_speed * current_camera.camera_front.z;
	}
	if (keyboard_state[SDL_SCANCODE_LEFT] || keyboard_state[SDL_SCANCODE_A]) {
		position normalized_front_up = normalize_vector(cross_product_vector(current_camera.camera_front, current_camera.camera_up));
		current_camera.camera_eye.x -= camera_speed * normalized_front_up.x;
		current_camera.camera_eye.y -= camera_speed * normalized_front_up.y;
		current_camera.camera_eye.z -= camera_speed * normalized_front_up.z;
	}
}
