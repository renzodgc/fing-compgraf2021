// HEADERS
// -----------------------------------------------------------------------------------
#include "camera_helper.h"

// NAMESPACE
// -----------------------------------------------------------------------------------
using namespace std;

// METHODS
// -----------------------------------------------------------------------------------


// FREE CAMERA
position FreeCamera::update_camera_front(float mouse_offset_x, float mouse_offset_y, float &yaw, float &pitch) {
	yaw += mouse_offset_x;
	pitch += mouse_offset_y;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	return normalize_vector({
		cos(degree_to_radian(yaw)) * cos(degree_to_radian(pitch)),
		sin(degree_to_radian(pitch)),
		sin(degree_to_radian(yaw)) * cos(degree_to_radian(pitch))
		});
}

void FreeCamera::update_camera_eye(float camera_speed, const Uint8* keyboard_state, position camera_front, position camera_up, position& camera_eye) {
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
