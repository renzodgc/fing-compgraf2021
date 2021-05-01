// HEADERS
// -----------------------------------------------------------------------------------
#include "camera_manager.h"

// NAMESPACE
// -----------------------------------------------------------------------------------
using namespace std;

// METHODS
// -----------------------------------------------------------------------------------

// GENERIC

void Camera::update_position(position player_position, double elapsed_time, const Uint8* keyboard_state) {
	switch (selected_camera) {
	case CameraType::isometric:
		isometric_camera_update_position(player_position);
		break;
	case CameraType::third_person:
		third_person_camera_update_position(player_position);
		break;
	case CameraType::free_view:
		free_view_camera_update_position(elapsed_time, keyboard_state);
		break;
	}
}

void Camera::update_angle(float mouse_offset_x, float mouse_offset_y) {
	switch (selected_camera) {
	case CameraType::isometric:
		// Do nothing
		break;
	case CameraType::third_person:
		third_person_camera_update_angle(mouse_offset_x, mouse_offset_y);
		break;
	case CameraType::free_view:
		free_view_camera_update_angle(mouse_offset_x, mouse_offset_y);
		break;
	}
}

void Camera::call_look_at() {
	switch (selected_camera) {
	case CameraType::isometric:
		gluLookAt(
			camera_eye.x, camera_eye.y, camera_eye.z,
			camera_front.x, camera_front.y, camera_front.z,
			camera_up.x, camera_up.y, camera_up.z
		);
		break;
	case CameraType::third_person:
		gluLookAt(
			camera_eye.x, camera_eye.y, camera_eye.z,
			camera_eye.x + camera_front.x, camera_eye.y + camera_front.y, camera_eye.z + camera_front.z,
			camera_up.x, camera_up.y, camera_up.z
		);
		break;
	case CameraType::free_view:
		gluLookAt(
			camera_eye.x, camera_eye.y, camera_eye.z,
			camera_eye.x + camera_front.x, camera_eye.y + camera_front.y, camera_eye.z + camera_front.z,
			camera_up.x, camera_up.y, camera_up.z
		);
		break;
	}
}

// ORTHOGONAL CAMERA

// Reference: https://stackoverflow.com/questions/1059200/true-isometric-projection-with-opengl
// Read reference for 2d view
void Camera::start_isometric_view(position player_position) {
	float distance = (float)sqrt(1 / 3.0);
	double scale = 10.;

	selected_camera = CameraType::isometric;
	camera_eye = { 1.f, 1.f, 1.f };
	camera_front = { 0.f, 0.f, 0.f };
	camera_up = { 0.f, 1.f, 0.f };
	yaw = -90.0f; // Initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
	pitch = 0.0f;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); // Reset the view

	glClearColor(LIGHT_GREY.red, LIGHT_GREY.green, LIGHT_GREY.blue, LIGHT_GREY.alpha);
	glOrtho(-scale, scale, -scale * 0.7, scale * 0.7, -scale, scale);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); // Reset the view

	glRotatef(35.264f, 1.0f, 0.0f, 0.0f);
	glRotatef(-45.0f, 0.0f, 1.0f, 0.0f);
}

void Camera::isometric_camera_update_position(position player_position) {};

// THIRD PERSON CAMERA
void Camera::start_third_person_view(position player_position) {
	selected_camera = CameraType::third_person;
	camera_eye = { 0.f, 0.f, 1.f };
	camera_front = { 0.f, 0.f, -1.f };
	camera_up = { 0.f, 1.f, 0.f };
	yaw = -90.0f; // Initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
	pitch = 0.0f;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); // Reset the view

	glClearColor(LIGHT_GREY.red, LIGHT_GREY.green, LIGHT_GREY.blue, LIGHT_GREY.alpha);
	gluPerspective(45., SCR_WIDTH / (float)SCR_HEIGHT, 0.1, 100.);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); // Reset the view
}

void Camera::third_person_camera_update_position(position player_position) {};

void Camera::third_person_camera_update_angle(float mouse_offset_x, float mouse_offset_y) {};

// FREE CAMERA
void Camera::start_free_view(position player_position) {
	selected_camera = CameraType::free_view;
	camera_eye = { 0.f, 0.f, 1.f };
	camera_front = { 0.f, 0.f, -1.f };
	camera_up = { 0.f, 1.f, 0.f };
	yaw = -90.0f; // Initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
	pitch = 0.0f;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); // Reset the view

	glClearColor(LIGHT_GREY.red, LIGHT_GREY.green, LIGHT_GREY.blue, LIGHT_GREY.alpha);
	gluPerspective(45., SCR_WIDTH / (float)SCR_HEIGHT, 0.1, 100.);
	glEnable(GL_DEPTH_TEST);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); // Reset the view
}

void Camera::free_view_camera_update_position(double elapsed_time, const Uint8* keyboard_state) {
	float camera_speed = (float)(MOVEMENT_CAMERA_SPEED * elapsed_time);
	if (keyboard_state[SDL_SCANCODE_UP] || keyboard_state[SDL_SCANCODE_W]) {
		camera_eye.x += camera_speed * camera_front.x;
		camera_eye.y += camera_speed * camera_front.y;
		camera_eye.z += camera_speed * camera_front.z;
	}
	if (keyboard_state[SDL_SCANCODE_RIGHT] || keyboard_state[SDL_SCANCODE_D]) {
		position normalized_front_up = normalize_vector(cross_product_vector(camera_front, camera_up));
		camera_eye.x += camera_speed * normalized_front_up.x;
		camera_eye.y += camera_speed * normalized_front_up.y;
		camera_eye.z += camera_speed * normalized_front_up.z;
	}
	if (keyboard_state[SDL_SCANCODE_DOWN] || keyboard_state[SDL_SCANCODE_S]) {
		camera_eye.x -= camera_speed * camera_front.x;
		camera_eye.y -= camera_speed * camera_front.y;
		camera_eye.z -= camera_speed * camera_front.z;
	}
	if (keyboard_state[SDL_SCANCODE_LEFT] || keyboard_state[SDL_SCANCODE_A]) {
		position normalized_front_up = normalize_vector(cross_product_vector(camera_front, camera_up));
		camera_eye.x -= camera_speed * normalized_front_up.x;
		camera_eye.y -= camera_speed * normalized_front_up.y;
		camera_eye.z -= camera_speed * normalized_front_up.z;
	}
}

void Camera::free_view_camera_update_angle(float mouse_offset_x, float mouse_offset_y) {
	yaw += mouse_offset_x;
	pitch += mouse_offset_y;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	camera_front = normalize_vector({
		cos(degree_to_radian(yaw)) * cos(degree_to_radian(pitch)),
		sin(degree_to_radian(pitch)),
		sin(degree_to_radian(yaw)) * cos(degree_to_radian(pitch))
	});
}
